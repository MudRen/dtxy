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
		name = HIY"��"HIG"��"HIB"ħ"HIR"��"YELGRN"ʯ"NOR;
		set("super_stone", 10+random(25));
		set("effect/gold", 10+random(25));
		set("effect/wood", 10+random(25));
		set("effect/water", 10+random(25));
		set("effect/fire", 10+random(25));
		set("effect/earth", 10+random(25));
		set("long","һ�鼫�亱���ľ�����������ħ���ı�ʯ��\n");
		set("value",100000000);
		set_name(name, ({"stone"+random(10000), "magic stone", "stone"}));
        set_weight(500);
        set("unit","��");
        set("material","stone");
        set("register_cost", 5000);

        if( clonep() )
                set_default_object(__FILE__);
        setup();
}
