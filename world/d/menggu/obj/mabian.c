inherit ITEM;
#include <ansi.h>
void create()
{
        set_name("���˵������", ({"muma bian", "bian" ,"whip"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ����ޣ�����ͨ������ޡ�\n");
                set("unit", "��");
        }
}

