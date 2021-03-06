#include <ansi.h>

void set_armor(object armor,string id) {
  int value;
  armor->set("no_break",1);
  armor->set_weight(600);
  armor->set("long", "附有特殊力量的装备，是大唐西游的新产物。");
  armor->set("material", "dark");
  armor->set("maximum_level", 14);//等级 1－14maximum_level
  armor->set("max_level", 14);//等级 1－14
  armor->set("level", 14);

  //附加属性
  switch (random(5)) {
  case 0:
          armor->set("armor_prop/gold_defense", 60);
          break;
  case 1:
          armor->set("armor_prop/wood_defense", 60);
          break;
  case 2:
          armor->set("armor_prop/water_defense", 60);
          break;
		case 3:
          armor->set("armor_prop/fire_defense", 60);
          break;
  case 4:
          armor->set("armor_prop/earth_defense", 60);
          break;
  }
  armor->set("armor_prop/armor", 15 + 75);//防御力
  if (!armor->is_acc()) {
          armor->set("sockets/max", 4);//安放宝石数
          armor->set("sockets/now", 0);
  }
  armor->set("wield/daoxing", 100000);
  armor->set("wield/int", 50);
  //价值
  value = 200000;
  value += armor->query("sockets/max") * 2000;
  value += armor->query("armor_prop/armor") * 1000;
  armor->set("value", value * 7);
armor->set("armor_prop/armor", 280);
  armor->set("mod/level",14);
  if (armor->query("armor_type") == "armor") {
	armor->set_name(HIR+BLK"天使宝甲"NOR,({"armor"+random(1000),"angel armor","armor"}));
  } else if (armor->query("armor_type") == "head") {
	armor->set_name(HIR+BLK"天使神盔"NOR,({"hat"+random(1000),"angel hat","hat"}));
  } else if (armor->query("armor_type") == "neck") {
	armor->set_name(HIR+BLK"天使项链"NOR,({"neck"+random(1000),"angel neck","neck"}));
  } else if (armor->query("armor_type") == "cloth") {
	armor->set_name(HIR+BLK"天使神衣"NOR,({"cloth"+random(1000),"angel cloth","cloth"}));
  } else if (armor->query("armor_type") == "surcoat") {
	armor->set_name(HIR+BLK"天使披风"NOR,({"cloak"+random(1000),"angel cloak","cloak"}));
  } else if (armor->query("armor_type") == "waist") {
	armor->set_name(HIR+BLK"天使腰带"NOR,({"waist"+random(1000),"angel waist","waist"}));
  } else if (armor->query("armor_type") == "wrists") {
	armor->set_name(HIR+BLK"天使神镯"NOR,({"wrists"+random(1000),"angel wrists","wrists"}));
  } else if (armor->query("armor_type") == "shield") {
	armor->set_name(HIR+BLK"天使盾"NOR,({"shield"+random(1000),"angel shield","shield"}));
  } else if (armor->query("armor_type") == "finger") {
	armor->set_name(HIR+BLK"天使戒"NOR,({"ring"+random(1000),"angel ring","ring"}));
  } else if (armor->query("armor_type") == "hands") {
	armor->set_name(HIR+BLK"天使护手"NOR,({"gloves"+random(1000),"angel gloves","gloves"}));
  } else if (armor->query("armor_type") == "boots") {
	armor->set_name(HIR+BLK"天使神鞋"NOR,({"shoes"+random(1000),"angel shoes","shoes"}));
  }
}

