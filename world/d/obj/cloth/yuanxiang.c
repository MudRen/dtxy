// yuanxiang.c ����Ь

#include <armor.h>
#include <ansi.h>

inherit BOOTS;


void create()
{
	set_name(RED "����Ь" NOR, ({ "shoes","yuanxiang","xie","yuanxiangxie" }) );
	set_weight(900);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "һ˫С���������廨Ь��  \n");
		set("material", "cloth");
		set("unit", "˫");
		set("value", 2000);
		set("armor_prop/armor", 1 );
		set("armor_prop/personality", 3);
		set("female_only", 1);
	}
	setup();
}

