// blade.c

#include <weapon.h>

inherit WHIP;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
        set_name("��", ({"whip"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","һ�ֹ�ע�������ıޣ�");
                set("unit", "��");
                set("value", 500);
        }
        init_whip(15);
        setup();
}

