// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// shoupi.c

#include <armor.h>
inherit NEWITEM;

inherit FINGER;

int is_acc() {
    return 1;
}

void create()
{
          set_name("戒指", ({"ring"}));
   set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "iron");
                  set("unit", "枚");
     set("armor_prop/armor", 1);
        }
        setup();
}

