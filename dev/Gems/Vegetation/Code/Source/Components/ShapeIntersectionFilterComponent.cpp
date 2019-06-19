/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include "Vegetation_precompiled.h"
#include "ShapeIntersectionFilterComponent.h"
#include <AzCore/Component/Entity.h>
#include <AzCore/Debug/Profiler.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <LmbrCentral/Shape/ShapeComponentBus.h>
#include <Vegetation/InstanceData.h>

#include <Vegetation/Ebuses/DebugNotificationBus.h>

namespace Vegetation
{
    void ShapeIntersectionFilterConfig::Reflect(AZ::ReflectContext* context)
    {
        AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context);
        if (serialize)
        {
            serialize->Class<ShapeIntersectionFilterConfig, AZ::ComponentConfig>()
                ->Version(0)
                ->Field("FilterStage", &ShapeIntersectionFilterConfig::m_filterStage)
                ->Field("ShapeEntityId", &ShapeIntersectionFilterConfig::m_shapeEntityId)
                ;

            AZ::EditContext* edit = serialize->GetEditContext();
            if (edit)
            {
                edit->Class<ShapeIntersectionFilterConfig>(
                    "Vegetation Shape Intersection Filter", "")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::ComboBox, &ShapeIntersectionFilterConfig::m_filterStage, "Filter Stage", "Determines if filter is applied before (PreProcess) or after (PostProcess) modifiers.")
                    ->EnumAttribute(FilterStage::Default, "Default")
                    ->EnumAttribute(FilterStage::PreProcess, "PreProcess")
                    ->EnumAttribute(FilterStage::PostProcess, "PostProcess")
                    ->DataElement(0, &ShapeIntersectionFilterConfig::m_shapeEntityId, "Shape Entity Id", "Entity with shape component to test intersection.")
                    ->Attribute(AZ::Edit::Attributes::RequiredService, AZ_CRC("ShapeService", 0xe86aa5fe))
                    ;

            }
        }

        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<ShapeIntersectionFilterConfig>()
                ->Attribute(AZ::Script::Attributes::ExcludeFrom, AZ::Script::Attributes::ExcludeFlags::Preview)
                ->Attribute(AZ::Script::Attributes::Category, "Vegetation")
                ->Constructor()
                ->Property("filterStage",
                    [](ShapeIntersectionFilterConfig* config) { return (AZ::u8&)(config->m_filterStage); },
                    [](ShapeIntersectionFilterConfig* config, const AZ::u8& i) { config->m_filterStage = (FilterStage)i; })
                ->Property("shapeEntityId", BehaviorValueProperty(&ShapeIntersectionFilterConfig::m_shapeEntityId))
                ;
        }
    }

    void ShapeIntersectionFilterComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& services)
    {
        services.push_back(AZ_CRC("VegetationFilterService", 0x9f97cc97));
        services.push_back(AZ_CRC("VegetationShapeInersectionFilterService", 0x36dcda80));
    }

    void ShapeIntersectionFilterComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& services)
    {
        services.push_back(AZ_CRC("VegetationShapeInersectionFilterService", 0x36dcda80));
    }

    void ShapeIntersectionFilterComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& services)
    {
        services.push_back(AZ_CRC("VegetationAreaService", 0x6a859504));
    }

    void ShapeIntersectionFilterComponent::Reflect(AZ::ReflectContext* context)
    {
        ShapeIntersectionFilterConfig::Reflect(context);

        AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context);
        if (serialize)
        {
            serialize->Class<ShapeIntersectionFilterComponent, AZ::Component>()
                ->Version(0)
                ->Field("Configuration", &ShapeIntersectionFilterComponent::m_configuration)
                ;
        }

        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Constant("ShapeIntersectionFilterComponentTypeId", BehaviorConstant(ShapeIntersectionFilterComponentTypeId));

            behaviorContext->Class<ShapeIntersectionFilterComponent>()->RequestBus("ShapeIntersectionFilterRequestBus");

            behaviorContext->EBus<ShapeIntersectionFilterRequestBus>("ShapeIntersectionFilterRequestBus")
                ->Attribute(AZ::Script::Attributes::ExcludeFrom, AZ::Script::Attributes::ExcludeFlags::Preview)
                ->Attribute(AZ::Script::Attributes::Category, "Vegetation")
                ->Event("GetShapeEntityId", &ShapeIntersectionFilterRequestBus::Events::GetShapeEntityId)
                ->Event("SetShapeEntityId", &ShapeIntersectionFilterRequestBus::Events::SetShapeEntityId)
                ->VirtualProperty("ShapeEntityId", "GetShapeEntityId", "SetShapeEntityId")
                ;
        }
    }

    ShapeIntersectionFilterComponent::ShapeIntersectionFilterComponent(const ShapeIntersectionFilterConfig& configuration)
        : m_configuration(configuration)
    {
    }

    void ShapeIntersectionFilterComponent::Activate()
    {
        SetupDependencyMonitor();
        ShapeIntersectionFilterRequestBus::Handler::BusConnect(GetEntityId());
    }

    void ShapeIntersectionFilterComponent::Deactivate()
    {
        FilterRequestBus::Handler::BusDisconnect();
        m_dependencyMonitor.Reset();
        ShapeIntersectionFilterRequestBus::Handler::BusDisconnect();
    }

    bool ShapeIntersectionFilterComponent::ReadInConfig(const AZ::ComponentConfig* baseConfig)
    {
        if (auto config = azrtti_cast<const ShapeIntersectionFilterConfig*>(baseConfig))
        {
            m_configuration = *config;
            return true;
        }
        return false;
    }

    bool ShapeIntersectionFilterComponent::WriteOutConfig(AZ::ComponentConfig* outBaseConfig) const
    {
        if (auto config = azrtti_cast<ShapeIntersectionFilterConfig*>(outBaseConfig))
        {
            *config = m_configuration;
            return true;
        }
        return false;
    }

    bool ShapeIntersectionFilterComponent::Evaluate(const InstanceData& instanceData) const
    {
        AZ_PROFILE_FUNCTION(AZ::Debug::ProfileCategory::Entity);

        bool inside = false;
        LmbrCentral::ShapeComponentRequestsBus::EventResult(inside, m_configuration.m_shapeEntityId, &LmbrCentral::ShapeComponentRequestsBus::Events::IsPointInside, instanceData.m_position);
        if (!inside)
        {
            VEG_PROFILE_METHOD(DebugNotificationBus::QueueBroadcast(&DebugNotificationBus::Events::FilterInstance, instanceData.m_id, AZStd::string_view("ShapeIntersectionFilter")));
        }
        return inside;
    }

    void ShapeIntersectionFilterComponent::SetupDependencyMonitor()
    {
        m_dependencyMonitor.Reset();
        m_dependencyMonitor.ConnectOwner(GetEntityId());

        if (m_configuration.m_shapeEntityId.IsValid())
        {
            m_dependencyMonitor.ConnectDependency(m_configuration.m_shapeEntityId);
            FilterRequestBus::Handler::BusConnect(GetEntityId());
        }
    }

    FilterStage ShapeIntersectionFilterComponent::GetFilterStage() const
    {
        return m_configuration.m_filterStage;
    }

    void ShapeIntersectionFilterComponent::SetFilterStage(FilterStage filterStage)
    {
        m_configuration.m_filterStage = filterStage;
        LmbrCentral::DependencyNotificationBus::Event(GetEntityId(), &LmbrCentral::DependencyNotificationBus::Events::OnCompositionChanged);
    }

    AZ::EntityId ShapeIntersectionFilterComponent::GetShapeEntityId() const
    {
        return m_configuration.m_shapeEntityId;
    }

    void ShapeIntersectionFilterComponent::SetShapeEntityId(AZ::EntityId shapeEntityId)
    {
        m_configuration.m_shapeEntityId = shapeEntityId;
        SetupDependencyMonitor();
        LmbrCentral::DependencyNotificationBus::Event(GetEntityId(), &LmbrCentral::DependencyNotificationBus::Events::OnCompositionChanged);
    }

}