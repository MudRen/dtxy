// whip.c

#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(HIR"�һ��"NOR, ({"liehuo bian","whip"}));
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",YEL"�Ϲ�ʮ�����֮һ���һ��\n"NOR);
                set("unit", "��");
                set("no_put",1);
                set("value", 0);
                set("no_zm",1);
                set("no_give",1);

        }
        init_whip(151+random(30));
        setup();
}

