// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// shoupi.c

#include <armor.h>

inherit WRISTS;
inherit NEWITEM;

int is_acc() {
    return 1;
}

void create()
{
        set_name("����", ({"wrists"}));
   set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "iron");
                set("unit", "��");
     set("armor_prop/armor", 1);
        }
        setup();
}

