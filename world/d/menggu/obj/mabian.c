inherit ITEM;
#include <ansi.h>
void create()
{
        set_name("老人的牧马鞭", ({"muma bian", "bian" ,"whip"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一根马鞭，很普通的牧马鞭。\n");
                set("unit", "根");
        }
}

