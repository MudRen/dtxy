
#include <weapon.h>

inherit BOW; 

void create()
{
  set_name("�������", ({ "jiutian arrow", "arrow", }) );
  set_weight(1000);
  if( clonep() )
  	set_default_object(__FILE__);
  else {
    set("long",
"������������칬��������������\n��۴����˺��ࡣ\n");
    set("unit", "��");
		set("value", 100);
                set("wield_msg", "$Nץ��һ��$n���������е�������\n");
                set("material", "wood");
  }
  init_bow(1);
  setup();
}

