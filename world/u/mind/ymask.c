#include <armor.h>
inherit EQUIP;

void create()
{
        set_name("�������", ({ "silver mask" ,"mask"}) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 800);
                set("material", "silver");
                set("armor_type", "mask");
                set("armor_prop/id", ({"yesi"}) );
                set("armor_prop/name", ({"Ү˿"}) );
                set("armor_prop/short", ({"Ү˿(yesi)"}) );
                set("armor_prop/long", ({
                        "�����������������ͨ�񣬷������ε�Ү˿��\n"
                }) );
        }
}
