#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_BOLT PT_BOLT 177
Element_BOLT::Element_BOLT()
{
	Identifier = "DEFAULT_PT_BOLT";
	Name = "BOLT";
	Colour = PIXPACK(0x263239);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.75f;
	HotAir = 0.001f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 1;

	Temperature = R_TEMP+2.0f	+273.15f;
	HeatConduct = 106;
	Description = "Gas that creates lightnings and fusionates to HYGN on heat. Very unstable! Freezes to VIBR at around absolute zero.";

	State = ST_GAS;
	Properties = TYPE_GAS|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 10;
	LowTemperatureTransition = PT_VIBR;
	HighTemperature = 9000;
	HighTemperatureTransition = PT_H2;

	Update = &Element_BOLT::update;
}

//#TPT-Directive ElementHeader Element_BOLT static int update(UPDATE_FUNC_ARGS)
int Element_BOLT::update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 2000.0 or sim->pv[y/CELL][x/CELL] > 100.0f) {
        parts[i].life = rand() % 100;
	}
	if (parts[i].life == 1) {
        int offx = (rand()%2) - 1;
        int offy = (rand()%2) - 1;
        sim->create_part(-1, x+offx, y+offy, PT_LIGH);
        parts[(pmap[y+offy][x+offx]>>8)].life = 5;
        parts[i].life = 0;
        parts[i].temp = R_TEMP;
	}
}

Element_BOLT::~Element_BOLT() {}