//Cracked by Roath
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
    set_name(HIR"???????۵?Т??"NOR,({"cloth"}));
   set_weight(3000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "??");
     set("material", "cloth");
     set("armor_prop/armor", 5);
   }
   setup();
}
