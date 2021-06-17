/*
  created by emotion
*/
#include <ansi.h>
inherit ITEM;
inherit NEWITEM;

int is_magic_stone() {
	return 1;
}

int is_super_stone() {
	return 1;
}

void create()
{
		int temp;
		string name;
		name = HIY"五"HIG"彩"HIB"魔"HIR"法"YELGRN"石"NOR;
		set("super_stone", 10+random(25));
		set("effect/gold", 10+random(25));
		set("effect/wood", 10+random(25));
		set("effect/water", 10+random(25));
		set("effect/fire", 10+random(25));
		set("effect/earth", 10+random(25));
		set("long","一块极其罕见的具有所有五行魔法的宝石。\n");
		set("value",100000000);
		set_name(name, ({"stone"+random(10000), "magic stone", "stone"}));
        set_weight(500);
        set("unit","颗");
        set("material","stone");
        set("register_cost", 5000);

        if( clonep() )
                set_default_object(__FILE__);
        setup();
}
