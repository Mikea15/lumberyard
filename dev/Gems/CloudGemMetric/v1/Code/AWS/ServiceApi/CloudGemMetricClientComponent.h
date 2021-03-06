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
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// THIS CODE IS AUTOGENERATED, DO NOT MODIFY
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
#pragma once
#include <AzCore/Component/Component.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/ComponentBus.h>
#include <AzCore/EBus/EBus.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/std/smart_ptr/make_shared.h>
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <AzCore/std/string/conversions.h>

#if defined (PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
#include <aws/core/http/HttpRequest.h>
#include <aws/core/http/HttpResponse.h>
#endif // (PLATFORM_SUPPORTS_AWS_NATIVE_SDK)

#include <CloudGemFramework/ServiceRequestJob.h>


#include "StdAfx.h"



namespace CloudGemMetric {
namespace ServiceAPI {
    
    extern const char* LmbrAWS_CodeGen_Priority_UUID;
    
    extern const char* LmbrAWS_CodeGen_ProduceResponse_UUID;
    
    extern const char* LmbrAWS_CodeGen_Component_UUID;
    
    extern const char* LmbrAWS_CodeGen_ResponseHandler_UUID;
    
    extern const char* LmbrAWS_CodeGen_NotificationBus1_UUID;
    
    extern const char* LmbrAWS_CodeGen_RequestBus1_UUID;
    
    extern const char* LmbrAWS_CodeGen_Filter_UUID;
    
    extern const char* LmbrAWS_CodeGen_ServiceStatus_UUID;
    
    extern const char* LmbrAWS_CodeGen_Payload_UUID;
    
    extern const char* LmbrAWS_CodeGen_ClientContext_UUID;
    

    // redefs
    
    using FilterAttributeItem = AZStd::string;
    

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const int& item);

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const AZStd::string& item);

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const double& item);

    
    
    struct Payload
    {

        AZ_TYPE_INFO(Payload, LmbrAWS_CodeGen_Payload_UUID)
        AZ_CLASS_ALLOCATOR(Payload, AZ::SystemAllocator, 0)

        
        AZStd::string data;
        

        bool OnJsonKey(const char* key, CloudGemFramework::JsonReader& reader);

        static void Reflect(AZ::ReflectContext* reflection);
    };

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const Payload& item);
    
    
    
    struct ProduceResponse
    {

        AZ_TYPE_INFO(ProduceResponse, LmbrAWS_CodeGen_ProduceResponse_UUID)
        AZ_CLASS_ALLOCATOR(ProduceResponse, AZ::SystemAllocator, 0)

        
        AZStd::string PhysicalResourceId;
        
        int StatusCode;
        

        bool OnJsonKey(const char* key, CloudGemFramework::JsonReader& reader);

        static void Reflect(AZ::ReflectContext* reflection);
    };

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const ProduceResponse& item);
    
    
    
    using FilterPropertyAttributes = AZStd::vector<FilterAttributeItem>;

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const FilterPropertyAttributes& list);
    
    
    
    struct Filter
    {

        AZ_TYPE_INFO(Filter, LmbrAWS_CodeGen_Filter_UUID)
        AZ_CLASS_ALLOCATOR(Filter, AZ::SystemAllocator, 0)

        
        FilterPropertyAttributes attributes;
        
        AZStd::string type;
        
        AZStd::string event;
        

        bool OnJsonKey(const char* key, CloudGemFramework::JsonReader& reader);

        static void Reflect(AZ::ReflectContext* reflection);
    };

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const Filter& item);
    
    
    
    using ClientContextPropertyFilters = AZStd::vector<Filter>;

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const ClientContextPropertyFilters& list);
    
    
    
    struct Priority
    {

        AZ_TYPE_INFO(Priority, LmbrAWS_CodeGen_Priority_UUID)
        AZ_CLASS_ALLOCATOR(Priority, AZ::SystemAllocator, 0)

        
        AZStd::string event;
        
        int precedence;
        

        bool OnJsonKey(const char* key, CloudGemFramework::JsonReader& reader);

        static void Reflect(AZ::ReflectContext* reflection);
    };

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const Priority& item);
    
    
    
    using ClientContextPropertyPriorities = AZStd::vector<Priority>;

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const ClientContextPropertyPriorities& list);
    
    
    
    struct ClientContext
    {

        AZ_TYPE_INFO(ClientContext, LmbrAWS_CodeGen_ClientContext_UUID)
        AZ_CLASS_ALLOCATOR(ClientContext, AZ::SystemAllocator, 0)

        
        int file_send_metrics_interval_in_seconds;
        
        ClientContextPropertyFilters filters;
        
        int file_threshold_to_prioritize_in_perc;
        
        double file_max_metrics_to_send_in_batch_in_mb;
        
        ClientContextPropertyPriorities priorities;
        
        int buffer_flush_to_file_max_in_bytes;
        
        double file_max_size_in_mb;
        
        int buffer_flush_to_file_interval_sec;
        

        bool OnJsonKey(const char* key, CloudGemFramework::JsonReader& reader);

        static void Reflect(AZ::ReflectContext* reflection);
    };

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const ClientContext& item);
    
    
    
    struct ServiceStatus
    {

        AZ_TYPE_INFO(ServiceStatus, LmbrAWS_CodeGen_ServiceStatus_UUID)
        AZ_CLASS_ALLOCATOR(ServiceStatus, AZ::SystemAllocator, 0)

        
        AZStd::string status;
        

        bool OnJsonKey(const char* key, CloudGemFramework::JsonReader& reader);

        static void Reflect(AZ::ReflectContext* reflection);
    };

    bool WriteJson(CloudGemFramework::JsonWriter& writer, const ServiceStatus& item);
    
    


    // Service RequestJobs
    CLOUD_GEM_SERVICE(CloudGemMetric);


    
    class SendMetricToSQSRequest
        : public CloudGemFramework::ServiceRequest
    {
    public:
        SERVICE_REQUEST(CloudGemMetric, HttpMethod::HTTP_POST, "/producer/produce/message");

        struct Parameters
        {
            
            Payload data;
            
            AZStd::string sensitivity_type;
            
            AZStd::string compression_mode;
            
            AZStd::string payload_type;
            

            bool BuildRequest(CloudGemFramework::RequestBuilder& request);

            bool WriteJson(CloudGemFramework::JsonWriter& writer) const;
        };

        
        ProduceResponse result;
        

        Parameters parameters;
    };


    using SendMetricToSQSRequestJob = CloudGemFramework::ServiceRequestJob<SendMetricToSQSRequest>;
    
    class GetClientContextDataRequest
        : public CloudGemFramework::ServiceRequest
    {
    public:
        SERVICE_REQUEST(CloudGemMetric, HttpMethod::HTTP_GET, "/clientcontext");

        struct Parameters
        {
            

            bool BuildRequest(CloudGemFramework::RequestBuilder& request);

            bool WriteJson(CloudGemFramework::JsonWriter& writer) const;
        };

        
        ClientContext result;
        

        Parameters parameters;
    };


    using GetClientContextDataRequestJob = CloudGemFramework::ServiceRequestJob<GetClientContextDataRequest>;
    
    class GetServiceStatusRequest
        : public CloudGemFramework::ServiceRequest
    {
    public:
        SERVICE_REQUEST(CloudGemMetric, HttpMethod::HTTP_GET, "/service/status");

        struct Parameters
        {
            

            bool BuildRequest(CloudGemFramework::RequestBuilder& request);

            bool WriteJson(CloudGemFramework::JsonWriter& writer) const;
        };

        
        ServiceStatus result;
        

        Parameters parameters;
    };


    using GetServiceStatusRequestJob = CloudGemFramework::ServiceRequestJob<GetServiceStatusRequest>;
    


    // Notification bus for this component
    class CloudGemMetricNotifications
        : public AZ::ComponentBus
    {
    public:
        
        /**
         * Sent when the request is a success
         *
         * Params:
         *    jsonOutput:       The output receieved from the lambda call
         *    request:          The AWS Lambda request object
         */
        
        virtual void OnSendMetricToSQSRequestSuccess(const ProduceResponse response);
        

        /**
         * Sent when the request fails
         *
         * Params:
         *    error:           The output receieved from the lambda call,
         *                     could be function error or an issue with the request
         *    request:         The AWS Lambda request object
         */
        virtual void OnSendMetricToSQSRequestError(const CloudGemFramework::Error error);
        
        /**
         * Sent when the request is a success
         *
         * Params:
         *    jsonOutput:       The output receieved from the lambda call
         *    request:          The AWS Lambda request object
         */
        
        virtual void OnGetClientContextDataRequestSuccess(const ClientContext response);
        

        /**
         * Sent when the request fails
         *
         * Params:
         *    error:           The output receieved from the lambda call,
         *                     could be function error or an issue with the request
         *    request:         The AWS Lambda request object
         */
        virtual void OnGetClientContextDataRequestError(const CloudGemFramework::Error error);
        
        /**
         * Sent when the request is a success
         *
         * Params:
         *    jsonOutput:       The output receieved from the lambda call
         *    request:          The AWS Lambda request object
         */
        
        virtual void OnGetServiceStatusRequestSuccess(const ServiceStatus response);
        

        /**
         * Sent when the request fails
         *
         * Params:
         *    error:           The output receieved from the lambda call,
         *                     could be function error or an issue with the request
         *    request:         The AWS Lambda request object
         */
        virtual void OnGetServiceStatusRequestError(const CloudGemFramework::Error error);
        
    };

    using CloudGemMetricNotificationBus = AZ::EBus<CloudGemMetricNotifications>;

    class BehaviorCloudGemMetricNotificationBusHandler
        : public CloudGemMetricNotificationBus::Handler, public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorCloudGemMetricNotificationBusHandler, LmbrAWS_CodeGen_NotificationBus1_UUID, AZ::SystemAllocator
        
        , OnSendMetricToSQSRequestSuccess
        , OnSendMetricToSQSRequestError
        
        , OnGetClientContextDataRequestSuccess
        , OnGetClientContextDataRequestError
        
        , OnGetServiceStatusRequestSuccess
        , OnGetServiceStatusRequestError
        
        );
        
        
        void OnSendMetricToSQSRequestSuccess(const ProduceResponse response) override;
        
        void OnSendMetricToSQSRequestError(const CloudGemFramework::Error error) override;
        
        
        void OnGetClientContextDataRequestSuccess(const ClientContext response) override;
        
        void OnGetClientContextDataRequestError(const CloudGemFramework::Error error) override;
        
        
        void OnGetServiceStatusRequestSuccess(const ServiceStatus response) override;
        
        void OnGetServiceStatusRequestError(const CloudGemFramework::Error error) override;
        
    };
    class CloudGemMetricResponseHandler;

    // Request bus for this component
    class CloudGemMetricRequests
        : public AZ::ComponentBus
    {
    public:
        virtual ~CloudGemMetricRequests() {}
        
        
        virtual void SendMetricToSQS(const Payload& data, const AZStd::string& sensitivity_type, const AZStd::string& compression_mode, const AZStd::string& payload_type, CloudGemMetricResponseHandler* responseHandler);
        
        
        
        virtual void GetClientContextData(CloudGemMetricResponseHandler* responseHandler);
        
        
        
        virtual void GetServiceStatus(CloudGemMetricResponseHandler* responseHandler);
        
        
    };

    using CloudGemMetricRequestBus = AZ::EBus<CloudGemMetricRequests>;

    // This class is used as a parameter for all requests and throws the response on the CloudGemMetricNotificationBus
    // Inherit from this to define custom behavior.
    class CloudGemMetricResponseHandler
    {
    public:
        AZ_TYPE_INFO(CloudGemMetricResponseHandler, LmbrAWS_CodeGen_ResponseHandler_UUID)
        AZ_CLASS_ALLOCATOR(CloudGemMetricResponseHandler, AZ::SystemAllocator, 0)

        virtual ~CloudGemMetricResponseHandler() {}
        
        virtual void HandleSendMetricToSQSSuccess(SendMetricToSQSRequestJob* job, AZ::EntityId entityId);
        virtual void HandleSendMetricToSQSError(SendMetricToSQSRequestJob* job, AZ::EntityId entityId);
        
        virtual void HandleGetClientContextDataSuccess(GetClientContextDataRequestJob* job, AZ::EntityId entityId);
        virtual void HandleGetClientContextDataError(GetClientContextDataRequestJob* job, AZ::EntityId entityId);
        
        virtual void HandleGetServiceStatusSuccess(GetServiceStatusRequestJob* job, AZ::EntityId entityId);
        virtual void HandleGetServiceStatusError(GetServiceStatusRequestJob* job, AZ::EntityId entityId);
        
    };

    class CloudGemMetricClientComponent
        : public AZ::Component
        , public CloudGemMetricRequestBus::Handler
    {
    public:
        AZ_COMPONENT(CloudGemMetricClientComponent, LmbrAWS_CodeGen_Component_UUID);
        virtual ~CloudGemMetricClientComponent() = default;

        AZStd::shared_ptr<CloudGemMetricResponseHandler> m_defaultResponseHandler;

        void Init() override;

        void Activate() override;

        void Deactivate() override;

        static void Reflect(AZ::ReflectContext* reflection)
        {
            
            
            Payload::Reflect(reflection);
            
            
            
            ProduceResponse::Reflect(reflection);
            
            
            
            
            
            Filter::Reflect(reflection);
            
            
            
            
            
            Priority::Reflect(reflection);
            
            
            
            
            
            ClientContext::Reflect(reflection);
            
            
            
            ServiceStatus::Reflect(reflection);
            
            

            AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(reflection);
            if (serializeContext)
            {
                // we must include any fields we want to expose to the editor or lua in the serialize context
                serializeContext->Class<CloudGemMetricClientComponent>()
                    ->Version(1);

                AZ::EditContext* editContext = serializeContext->GetEditContext();
                if (editContext)
                {
                    editContext->Class<CloudGemMetricClientComponent>("CloudGemMetricClientComponent", "CloudGemMetric Component")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                            ->Attribute(AZ::Edit::Attributes::Category, "Cloud Canvas Gems")
                            ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"));
                }
            }

            AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(reflection);
            if (behaviorContext)
            {
                behaviorContext->EBus<CloudGemMetricRequestBus>("CloudGemMetricRequestBus")
                    // one of these for each function
                    
                    ->Event("SendMetricToSQS", &CloudGemMetricRequestBus::Events::SendMetricToSQS)
                    
                    ->Event("GetClientContextData", &CloudGemMetricRequestBus::Events::GetClientContextData)
                    
                    ->Event("GetServiceStatus", &CloudGemMetricRequestBus::Events::GetServiceStatus)
                    
                    ;
                behaviorContext->EBus<CloudGemMetricNotificationBus>("CloudGemMetricNotificationBus")
                    ->Handler<BehaviorCloudGemMetricNotificationBusHandler>()
                ;
            }
        }

        // Functions from the swagger definitions
        
        
        void SendMetricToSQS(const Payload& data, const AZStd::string& sensitivity_type, const AZStd::string& compression_mode, const AZStd::string& payload_type, CloudGemMetricResponseHandler* responseHandler) override;
        
        
        
        void GetClientContextData(CloudGemMetricResponseHandler* responseHandler) override;
        
        
        
        void GetServiceStatus(CloudGemMetricResponseHandler* responseHandler) override;
        
        
    };
} // ServiceAPI
} // CloudGemMetric