#include <ansi.h> 
inherit F_UNIQUE;

inherit ITEM;
//inherit F_LIQUID;

void create()
{
        set_name(MAG"�Ϻ�«"NOR, ({"jiujianxian xinwu","xinwu","hulu"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "�ƽ����������װ�Ƶĺ�«��\n");
                set("unit", "��");
                set("value", 10);
                set("replace_file", "/d/ourhome/obj/hulu");
        }


}
