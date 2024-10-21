#pragma once
//se llama equipment enves de weapon pq tambn va a heredar de aca las armaduras
// de esta clase basicamente deberian heredar las clases que usan el boton de 'accion' 
// para usarse. Por ahora, las armas, granadas y aramduras.

class Equipment { 

    public:
        virtual void action() = 0;
        virtual void throw_equipment() = 0;

        virtual ~Equipment() = default;
};
