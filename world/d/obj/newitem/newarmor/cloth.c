// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// shoupi.c

#include <armor.h>

inherit CLOTH;
inherit NEWITEM;  // this line must be placed after the CLOTH, to overwrite the init defined in CLOTH

int is_armor() {
    return 1;
}

void create()
{
        set_name("����", ({"cloth"}));
   set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "��");
     set("armor_prop/armor", 1);
        }
        setup();
}
