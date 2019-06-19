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
#pragma once

#include <QBrush>
#include <QGraphicsItem>
#include <QPen>
#include <QTransform>

#include <AzCore/Component/TickBus.h>
#include <AzCore/Math/Vector2.h>
#include <AzCore/std/chrono/types.h>

#include <GraphCanvas/GraphicsItems/GraphicsEffect.h>

namespace GraphCanvas
{        
    namespace Styling
    {
        class StyleHelper;
    }

    class ParticleConfiguration
    {
    public:    
        enum class Shape
        {
            Circle,
            Square
        };
        
        Shape m_particleShape = Shape::Square;        
        
        const Styling::StyleHelper* m_styleHelper = nullptr;
        QColor m_color;
        
        AZStd::chrono::milliseconds m_lifespan = AZStd::chrono::milliseconds(250);
        
        bool m_rotate = false;
        float m_rotationSpeed = 0.0f;
        
        bool m_alphaFade = false;
        AZStd::chrono::milliseconds m_fadeTime = AZStd::chrono::milliseconds(250);
        float m_alphaStart = 1.0f;
        float m_alphaEnd = 0.0f;
        
        bool m_hasGravity = false;        
        
        QPointF m_initialImpulse = QPoint(0,0);
        
        QRectF m_boundingArea;
        float m_initialRotation = 0.0f;

        int m_zValue = 0;
    };
    
    class ParticleGraphicsItem
        : public GraphicsEffect<QGraphicsItem>
        , public AZ::TickBus::Handler
    {
    public:
        AZ_CLASS_ALLOCATOR(ParticleGraphicsItem, AZ::SystemAllocator, 0);
        
        ParticleGraphicsItem(const ParticleConfiguration& particleConfiguration);        
        
        // TickBus
        void OnTick(float deltaTime, AZ::ScriptTimePoint timePoint) override;
        ////
        
        // GraphicsItem
        QRectF boundingRect() const override;
        
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
        ////        
       
    private:
    
        ParticleConfiguration m_configuration;
        
        float m_elapsedDuration;
        QPointF m_impulse;

        QRectF m_boundingRect;
        QPainterPath m_clipPath;
    };
}