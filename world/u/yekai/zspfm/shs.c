 //sgzl
#include <ansi.h>

inherit NPC;
string ask_for_zspfm();
void create()
{
          set_name(HIW"沙和尚"NOR,({"sha heshang","sha","heshang"}));
          set("gender", "男性");
          set("title", HIY"金身罗汉"NOR);
		  set("long", @LONG
他就是习惯性打酱油的卷帘大将了。
曾经跟随唐僧西天取经，历尽千辛万苦，终于修成了正果。你可以问他有关"转世绝学"的消息。
LONG);
          set("age", 23);
          set("per",10);        
          set("combat_exp", 1800000);
	  set("daoxing",1500000);
          set("per", 30);
          set("str", 30);
          set("max_kee", 2200);
          set("kee",2200);
          set("force_factor",20);
          set("max_sen", 1800);
          set("sen",1800);
          set("force", 6000);
          set("max_force", 3000);
          set("max_mana", 3000);
          set("mana", 6000);
          set_skill("unarmed", 180+random(50));
          set_skill("dodge", 180+random(50));
          set_skill("force", 180+random(50));
          set_skill("parry", 180+random(50));
          set_skill("staff", 180+random(50));
          set_skill("spells", 180+random(50));
          set_skill("buddhism",180+random(50));
          set_skill("jienan-zhi", 180+random(50));
          set_skill("lotusforce", 180+random(50));
          set_skill("lotusmove", 180+random(50));
          set_skill("lunhui-zhang", 180+random(50));
          map_skill("spells", "buddhism");
          map_skill("unarmed", "jienan-zhi");
          map_skill("force", "lotusforce");
          map_skill("staff", "lunhui-zhang");
          map_skill("parry", "lunhui-zhang");
          map_skill("dodge", "lotusmove");
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
         carry_object("/d/qujing/liusha/obj/staff")->wield();
}

string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"你已经领悟了足够多的绝学了!\n"NOR;
	if (me->query("zspfm/zspfm_shs"))
		return HIY"我的绝学你已经掌握了！\n"NOR;
	if (me->query("lunhui_zhuanshi") < 2)
		return HIY"二转以上才能领悟我的绝学!\n"NOR;
	if (me->query("zspfm/zspfm_shs_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"你的修为还不够，领悟不到绝学!\n"NOR;
	me->add("zspfm/zspfm_shs_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_shs",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n【转世绝学】：恭喜"+me->query("name")+"在第"+chinese_number(me->query("zspfm/zspfm_shs_number"))+"次的时候领悟了金身罗汉的绝学！\n"NOR, users() );
		return HIY"恭喜恭喜，你成功领悟了我的绝学!\n"NOR;
	} else {
		return HIY"非常遗憾，你机缘不到，没能领悟我的绝学!\n"NOR;
	}
}


