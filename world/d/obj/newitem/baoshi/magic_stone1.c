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
		set("long","һ��ϡ�еľ��н�ϵħ���ı�ʯ��\n");
		set("value",100000);
		name = HIY"��ɫ��ʯ"NOR;
		set("effect/gold", 10+random(20));
		set_name(name, ({"stone"+random(10000), "magic stone", "stone"}));
        set_weight(500);
        set("unit","��");
        set("material","stone");

        if( clonep() )
                set_default_object(__FILE__);
        setup();
}
