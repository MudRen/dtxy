// jinjia.c ���
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name("�����", ({"qilin armor","armor", "jia", "qilin jia"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("no_give",1);
                set("no_drop",1);
                set("no_sell",1);
                set("unit", "��");
                set("long", "һ��������Ƭ���ɵı��ף�\n");
                set("material", "steel");
                set("armor_prop/armor",150);
                set("armor_prop/dodge", 100);
        }
        setup();
}


