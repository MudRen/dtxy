#include <ansi.h>
#include <armor.h>

//inherit F_UNIQUE;
inherit ARMOR;
inherit F_UNIQUE;


void create()
{
        set_name(HIC"ʥ��ս��"NOR, ({"shengyu armor","zhanjia", "jia", "armor"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("long", "һ�����������˿������ɽ�����������ɵĻ��ס�\n");
		set("no_sell", 1);
                set("no_drop", 1);
		set("no_put", 1);
                set("material", "crimsonsteel");
                set("value", 1000);
                set("armor_prop/armor", 100);
		set("replace_file", "/d/obj/cloth/hufa-jiasha");
		set("armor_prop/dodge", 5);
        }
        set("special_effects", "��");  // emotion
        setup();
}

