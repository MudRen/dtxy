
#include <weapon.h>

inherit BOW; 

void create()
{
  set_name("九天神箭", ({ "jiutian arrow", "arrow", }) );
  set_weight(1000);
  if( clonep() )
  	set_default_object(__FILE__);
  else {
    set("long",
"九天神箭乃是天宫宝物。后因九日作乱\n玉帝赐予了后羿。\n");
    set("unit", "副");
		set("value", 100);
                set("wield_msg", "$N抓起一张$n，握在手中当武器。\n");
                set("material", "wood");
  }
  init_bow(1);
  setup();
}

