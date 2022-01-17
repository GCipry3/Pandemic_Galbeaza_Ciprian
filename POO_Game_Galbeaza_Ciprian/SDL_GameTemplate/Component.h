#pragma once
class Component
{
public:
   virtual ~Component() = default;
   virtual void init() = 0;
   virtual void update() = 0;
   virtual void draw() = 0;
};