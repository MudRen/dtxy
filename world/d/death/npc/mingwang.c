//tomcat
//mingwang.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_jingtian();
void create()
{
  set_name("冥王", ({"ming wang", "wang"}));
  set("long", "他便是地藏王菩萨的师兄，与地藏王势不两立，因不服天庭管束被赶出地府．终日在鬼门关附近游荡。\n");
  set("title",CYN"幽冥之王"NOR);
  set("gender", "男性");
  set("class", "youling");
  set("age", 80);
  set("attitude", "friendly");
  set("shen_type", 1);
  set("per", 30);
  set("str", 60);
  set("int", 30+random(5));
  set("max_kee", 10000);
  set("max_sen", 10000);
  set("kee", 10000);
  set("sen", 10000);

  set("force", 12000);
  set("max_force", 6000);
  set("force_factor", 300);
  set("max_mana", 5000);
  set("mana", 10000);
  set("mana_factor", 300);

  set("combat_exp", 60000000);
  set("daoxing",10000000);

   set_skill("unarmed", 300);
   set_skill("whip", 300);
   set_skill("hellfire-whip", 300);
   set_skill("dodge", 300);
   set_skill("parry", 300);
   set_skill("literate", 300);
   set_skill("spells", 300);
   set_skill("force", 300);
   set_skill("tonsillit", 300);
   set_skill("ghost-steps", 300);
   set_skill("gouhunshu", 300);
   set_skill("jinghun-zhang", 300);
   set_skill("kusang-bang", 300);
   set_skill("zhuihun-sword", 300);
   set_skill("sword", 300);
   set_skill("stick", 300);

  map_skill("force", "tonsillit");
  map_skill("unarmed", "jinghun-zhang");
  map_skill("dodge", "ghost-steps");
  map_skill("spells", "gouhunshu");
  map_skill("parry", "hellfire-whip");
  map_skill("whip", "hellfire-whip");
  map_skill("sword", "zhuihun-sword");
  set("inquiry",([
      "惊天三式": (: ask_jingtian :),
      ]));
  set("jingtian_known",3);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword","yanluo" :),
		(: perform_action, "sword","jingtian" :),
                (: exert_function, "recover" :),
                (: cast_spell, "gouhun" :),
        }) );
 
  set_temp("apply/armor", 500);
  set_temp("apply/damage", 250);
  
  create_family("阎罗地府", 1, "祖师");
  setup();
  carry_object("/d/obj/cloth/baipao")->wear();
  carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}

 
void attempt_apprentice(object ob)
{
     object me;
     
      ob->this_player();
   
   if( (int)ob->query("family/generation")==2 )  
  {
        command("say 你是地藏的徒弟？，拿命来吧!");
        message_vision ("$n大喝一声要杀死$N！\n",me,ob);
        kill_ob(ob);
        return ;
   }   

    if (ob->query("obstacle/number") < 26) {
        command("say 这位" + RANK_D->query_respect(ob) + "你还是先出去闯荡一番吧！\n");
        command("sigh");
        return;
        }

    if (((int)ob->query("daoxing") < 1000000 )) {
      command("say " + RANK_D->query_rude(ob) + "这点三脚猫的把式怎么打得过地藏王？回去练练把!");
      return;
    }
    command("grin");
    command("say 很好，" + RANK_D->query_respect(ob) +
       "多加努力，他日帮我报仇，杀了地藏王这个老匹夫。\n");
    command("recruit " + ob->query("id") );
    return;
  }

int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
       ob->set("title", HBBLU"九幽鬼圣"NOR);
    ob->set("class", "youling");
}

string ask_jingtian()
{
	object me = this_player();
	object downroom = load_object(__DIR__"wuxing");
	if( !wizardp(me) && me->query("family/family_name") != "阎罗地府" )	
		return ("你不是幽冥鬼类，无法学习惊天三式！");
	if( me->query("betray/count") )
		return ("你三心二意无法领会惊天绝学。\n");
	if( me->query("jingtian_known") > 2 )
		return ("这惊天三式你都学会了，下面就要看你自己的了！");
	if( me->query("jingtian_cant") )
		return ("该学的你都学过了，不该学的，你也领会不了，莫要强求！");
	if( me->query("family/master_id") == "dizang pusa" )  
	        return ("你是地藏的徒弟？！");
	if( me->query_temp("jingtian/dizang") )
		return ("不是让你去干掉地藏的吗？！");
	if( me->query_temp("jingtian/jiejie") )
		return ("不是让你去破坏掉鬼门关的结界吗？！");
	if( !me->query("jingtian_known"))
	{
		if( me->query_skill("literate",1) < 200 )
			return ("就你这点学识，如何能领悟惊天绝学？");
		if( me->query_skill("zhuihun-sword",1) < 200 )
			return ("你的剑法太低了！");
		if( me->query_skill("tonsillit",1) < 200 )
			return ("你内功太低了！");
		me->set_temp("jingtian/dizang",1);
		command("say 好，果然有出息。");
		command("say 你先帮我把地藏干掉。");
		command("say 我地府虽是仙家，不过地府内充盈着愁怨仇恨的气息。");
		command("say 若是你能够炼化这些气息，就能大大增强自己的实力。");
	}
	if(me->query("jingtian_known")==1)
	{
		if( me->query_skill("literate",1) < 250 )
			return ("要领会更深的惊天绝学，你这点学识还不够！");
		if( me->query_skill("zhuihun-sword",1) < 250 )
			return ("你的剑法太低了！");
		if( me->query_skill("tonsillit",1) < 250 )
			return ("你内功太低了！");
		me->set_temp("jingtian/jiejie",1);
		command("say 好，果然有出息，杀了地藏出了我一口恶气。");
		command("say 不过鬼门关那道气墙实际是天庭和如来联手布下的结界。");
		command("say 当我领悟了惊天三式以后，地藏早已不是我的对手，所以他们才想出这个办法。");
		command("say 你帮我把那结界破(break)了，自此以后冥界就是你我的天下了。");
	}
	if(me->query("jingtian_known")==2)
	{
		if( me->query_skill("literate",1) < 300 )
			return ("要领会更深的惊天绝学，你这点学识还不够！");
		if( me->query_skill("zhuihun-sword",1) < 300 )
			return ("你的剑法太低了！");
		if( me->query_skill("tonsillit",1) < 300 )
			return ("你内功太低了！");
		me->set_temp("jingtian/lingwu",1);
		command("say 好，果然有出息，我们冥界实力强大，现在如来、玉帝也拿我们没办法了。");
		command("haha");
		command("say 这地府中就是奈何桥上的怨气最重，你去哪里修炼(xiulian)吧。");
		command("say 当年我就是在奈何桥上完全领悟了惊天三式的。");
		command("say 希望你早日领悟绝学，也为我冥界统一三界多做贡献。");
	}
	return ("又有好戏看了，嘿嘿！");
}