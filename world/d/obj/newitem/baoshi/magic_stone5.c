/*
  created by emotion
*/
#include <ansi.h>
inherit ITEM;
inherit NEWITEM;

int is_magic_stone() {
	return 1;
}

void create()
{
		int temp;
		string name;
		set("long","一块稀有的具有土系魔法的宝石。\n");
		set("value",100000);
		name = YELGRN"土色宝石"NOR;
		set("effect/earth", 10+random(20));
		set_name(name, ({"stone"+random(10000), "magic stone", "stone"}));
        set_weight(500);
        set("unit","颗");
        set("material","stone");

        if( clonep() )
                set_default_object(__FILE__);
        setup();
}
