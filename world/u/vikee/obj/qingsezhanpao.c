//qingsezhanpao.c
//vikee 2000.7.

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
	set_name(HIC"��˿ս��"NOR, ({"qingse zhanpao", "color cloth", "pao" }) );
	set("long", "����һҶ֪�ﻤ��ս�ۣ��þ������������ƶ��ɡ�\n");
	set_weight(0);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "cloth");
		set("armor_prop/armor", 500);
		set("armor_prop/dodge", 500);
                set("armor_prop/personality", 10);
                set("value", 50000);
              
	}
	setup();
}

