// created by wxb 12/24/1998
// room: /d/qujing/huangfeng/obj/mifan.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("?㵾?׷?", ({"xiangdao mifan", "mifan", "fan"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һ???㵾?׷???\n");
                set("unit", "??");
                set("value", 100);
                set("food_remaining", 2);
                set("food_supply", 100);
        }
}

