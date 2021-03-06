//【三界散仙】lestat 2001/8
// 鬼谷子

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string expell_me(object me);
string ask_icefire();
void create()
{
       set_name("鬼谷子", ({ "gui guzi", "guzi", "gui" }));
//        set("title","");
        set("long", 
"传说中的神仙，满头白发的老人，两眼炯炯有神。\n");

        set("gender", "男性");
        set("age", 665);
        set("attitude", "peaceful");
        set("str", 100);
        set("int", 40);
        set("con", 30);
        set("per", 20);
        set("class","sanxian");
        
        set("kee", 4000);
        set("max_kee", 4000);
        set("sen", 3000);
        set("max_sen", 3000);
        set("force", 15000);
        set("max_force", 8000);
        set("max_mana",8000);
        set("mana",12000);
        set("force_factor", 500);
        set("mana_factor", 500);
        set("combat_exp", 100000000);
        set("daoxing", 100000000);

        set_skill("spells",300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);   
        set_skill("binfen-steps", 300);        
        set_skill("literate", 300);
        set_skill("ice_fire_zhang", 300);
        set_skill("unarmed", 300);
        set_skill("whip", 300);
        set_skill("butian-force", 300);
        set_skill("mysticism", 300);
        set_skill("wuwei-fuchen", 300);
        set_skill("spysword", 300);        
        map_skill("dodge", "binfen-steps");        
        map_skill("parry", "spysword");
        map_skill("sword", "spysword");
        map_skill("force", "butian-force");
        map_skill("spells", "mysticism");
        map_skill("whip", "wuwei-fuchen");
         map_skill("unarmed", "ice_fire_zhang");
        set("inquiry",([
      		"冰火诀"    : (: ask_icefire :),
      			]));


        create_family("三界散仙", 1, " 白");
	set("icefire_known",2);
	set("old_flag/jiandao",10);
        set("chat_chance_combat", 90);
	   set("chat_msg_combat", 
	   ({
	     (: perform_action, "unarmed","icefire" :),
	     (: perform_action, "sword","bishou" :),
	     (: perform_action, "sword","dunnoname" :),
	     (: perform_action, "sword","dunnotruth" :),
	    }) );
   add_temp("apply/damage", 135);
   add_temp("apply/attack", 135);
   add_temp("apply/dodge", 135);
   add_temp("apply/spells", 100);
   add_temp("apply/armor", 150);
   add_temp("apply/armor_vs_force",250);
   add_temp("apply/armor_vs_spells",250);
   
        setup();
        carry_object("/d/obj/weapon/sword/qinghong")->wield();
        carry_object("/d/obj/cloth/choupao")->wear();
}
int is_ghost() { return 1; }

void attempt_apprentice(object ob)
{
   if ( (string)ob->query("family/family_name")=="三界散仙") {
if (ob->query("obstacle/number") < 26) {
command("say 这位" + RANK_D->query_respect(ob) + "拜我为师，要先先历尽取经劫难！\n");
 command("sigh");
 return;
}
  if (((int)ob->query("daoxing") < 1000000 )) {
   command("say " + RANK_D->query_respect(ob) +
"的道行不够高深，有些绝学秘法恐怕难以领悟。\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("recruit " + ob->query("id") );
        return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"我不认识你吧。\n");
        return;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
   ob->set("class", "sanxian");
   ob->set("title",HIB"鬼谷子传人"NOR);
   }

string ask_icefire()
{
	object me = this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法领会冰火诀。\n");
	if(me->query("family/family_name") != "三界散仙" )
                return ("你不是我散仙弟子!!\n");
        if(me->query("icefire_known") > 1 )
      		return ("冰火诀的口诀你都已经知道了啊！");
      	if(me->query("icefire_cant"))
      		return ("你无法领悟更高的冰火诀！");
      	if( me->query_skill("literate",1) < 200 )
		return ("你这点学识不足以领悟冰火诀！");
	if( me->query_skill("ice_fire_zhang",1) < 200 )
		return ("你这点掌法不足以领悟冰火诀！");
	if( me->query_skill("butian-force",1) < 200 )
		return ("你这点内功不足以领悟冰火诀！");	
	if( me->query_skill("wuwei-fuchen",1) < 200 )
		return ("你这点鞭法不足以领悟冰火诀！");	
      	command("addoil");
      	if( me->query("icefire") )
      	{
      		command("say 我等你的好消息！");
      	}
      	else if( !me->query("icefire_known") )
      	{
		me->set("icefire/ice",1);
		me->set("icefire/fire",1);
		command("say 要领悟冰火诀需要先领悟炎阳寒冰心法，并凝练出冰魄刀和寒冰刀。");
		command("say 冰窖火窟对你的帮助会很大，你就去哪里领悟（xiulian）吧。");
	}
	else
	{
		me->set("icefire/ice",3);
		me->set("icefire/fire",3);
		command("say 要想领悟更深的冰火诀，你必须能同时运转炎阳寒冰心法。");
		command("say 冰窖火窟对你的帮助会很大，你就去哪里领悟（xiulian）吧。");
	}
	return ("一切多加小心！");
}



