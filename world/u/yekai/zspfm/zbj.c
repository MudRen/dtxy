 //sgzl
#include <ansi.h>

inherit NPC;
string ask_for_zspfm();
void create()
{
  set_name(HIW"猪八戒"NOR,({"zhu bajie","zhu","bajie"}));
  set("gender", "男性");
  set("long",@LONG
他就是贪嗔痴俱全的天蓬元帅了。
曾经跟随唐僧西天取经，历尽千辛万苦，终于修成了正果。你可以问他有关"转世绝学"的消息。
LONG);
  set("title", HIY"净坛使者"NOR);
  set("age", 35);
  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 2000000);
  set("daoxing", 2000000);
  set("kee", 2600);
  set("max_kee", 2600);
  set("sen", 2800);
  set("max_sen", 2800);
  set("force", 7000);
  set("max_force", 3500);
  set("mana", 7000);
  set("max_mana", 3500);
  set("force_factor", 40);
  set("mana_factor", 40);
  set("str", 40);
  set("per", 10);

  set_skill("unarmed", 200+random(50));
  set_skill("dodge", 200+random(50));
  set_skill("parry", 200+random(50));
  set_skill("rake", 200+random(50));
  set_skill("force", 200+random(50));
  set_skill("spells", 200+random(50));
  set_skill("baguazhou", 200+random(50));
  set_skill("yanxing-steps", 200+random(50));
  set_skill("skyriver-rake", 200+random(50));
  map_skill("force", "lengquan-force");
  map_skill("spells", "baguazhou");
  map_skill("rake", "skyriver-rake");
  map_skill("parry", "skyriver-rake");
  map_skill("dodge", "yanxing-steps");
  
  set_temp("apply/attack", 200);
  set_temp("apply/defense", 200);
  set_temp("apply/armor", 200);
  set_temp("apply/damage", 200);  
  set("force_factor",300);
  set("mana_factor",300);
  set("bellicosity",300);
  set("nk_gain", 100+random(50));
  set("nk_factor", 12);
  set("inquiry", ([
                "转世绝学" : (: ask_for_zspfm :),
                ]) );
   setup();
}

string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"你已经领悟了足够多的绝学了!\n"NOR;
	if (me->query("zspfm/zspfm_zbj"))
		return HIY"我的绝学你已经掌握了！\n"NOR;
	if (me->query("lunhui_zhuanshi") < 3)
		return HIY"三转以上才能领悟我的绝学!\n"NOR;
	if (me->query("zspfm/zspfm_zbj_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"你的修为还不够，领悟不到绝学!\n"NOR;
	me->add("zspfm/zspfm_zbj_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_zbj",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n【转世绝学】：恭喜"+me->query("name")+"在第"+chinese_number(me->query("zspfm/zspfm_zbj_number"))+"次的时候领悟了净坛使者的绝学！\n"NOR, users() );
		return HIY"恭喜恭喜，你成功领悟了我的绝学!\n"NOR;
	} else {
		return HIY"非常遗憾，你机缘不到，没能领悟我的绝学!\n"NOR;
	}
}


