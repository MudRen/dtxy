// pangu.c 盘古
//lestat
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string jiebai();
string unjiebai();
string ask_kai();
void create()
{
        set_name(HIR"盘古"NOR, ({ "pan gu","gu" }) );
        set("title", HIR"开天辟地"NOR);
        set("gender", "男性" );
        set("age", 44);
        set("str", 100);
        set("cor", 30);
        set("cps", 30);
        set("int", 30);
        set("per", 30);
        set("kar", 60);
        set("long",
                "上古正神,开天辟地!\n");
        set("max_force", 15000);
        set("force", 15000);
        set("force_factor", 120);
        set("combat_exp", 10000000);
        set("daoxing", 10000000);
        set("attitude", "friendly");
        set("max_kee", 18000);
        set("max_sen", 18000);
        set_skill("parry", 300);
        set_skill("dodge", 300);
        set_skill("force", 300);
        set_skill("archery", 300);
        set_skill("literate", 300);
        set_skill("mace", 300);
        set_skill("unarmed", 300);
        set_skill("changquan", 300);
        set_skill("yanxing-steps", 300);
        set_skill("lengquan-force", 300);
        set_skill("spear", 300);
        set_skill("axe", 300);
        set_skill("baguazhou", 300);
        set_skill("spells", 300);
        set_skill("sanban-axe", 300);
        set("max_mana", 10000);
        set("mana", 15000);
        set("mana_factor", 450);
        map_skill("force", "lengquan-force");
        map_skill("unarmed", "changquan");
        map_skill("spells", "baguazhou");
        map_skill("axe", "sanban-axe");
        map_skill("parry", "sanban-axe");
        map_skill("dodge", "yanxing-steps");
        
        set_temp("apply/damage",300);
        set_temp("apply/armor",600);
        set("kai_known",3);
        set("chat_chance_combat", 90);
        set("chat_msg_combat", 
   	({
     		(: perform_action, "axe", "kai" :),
     		(: perform_action, "axe", "sanban" :),
    	}) );
        set("inquiry",([
      			"开天辟地": (: ask_kai :),
      			]));
        create_family("将军府", 1, "蓝");
        setup();
        carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/npc/obj/axe")->wield();
        
}



int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
    ob->set("class", "fighter");
    ob->set("title", HIR"盘古鬼斧传人"NOR);
}

void attempt_apprentice(object ob)
{
        ob=this_player();
  
  if (ob->query("obstacle/number") < 26) {
        command("say 这位" + RANK_D->query_respect(ob) + "你江湖阅历太浅了！\n");
        command("sigh");
        return;
        }
 if( (int)ob->query("pending/kick_out")) {
        command("say 这位" + RANK_D->query_respect(ob) + "老夫平生最恨不忠不义之人！\n");
        command("heng");
        return;
        }
  if (ob->query("combat_exp") < 1000000)
    {
       command("sigh");
       command("say 这位" + RANK_D->query_respect(ob) + "你武功根底太差了！\n");
       return ;
     }
    command("haha");
    command("recruit " + ob->query("id") );
    return 0;
}

string ask_kai()
{
	object me = this_player();
	object downroom = load_object(__DIR__"wuxing");
	if( !wizardp(me) && me->query("family/family_name") != "将军府" )	
		return ("不是我将军府弟子！");
	if( me->query("betray/count") )
		return ("你三心二意无法领会开天辟地绝学。\n");
	if( me->query("kai_known") > 2 )
		return ("这开天辟地的道理你都懂了，下面就要看你自己的了？");
	if( me->query("kai_cant") )
		return ("该学的你都学过了，不该学的，你也领会不了，莫要强求！");
	if( !me->query("kai_known"))
	{
		if( me->query_skill("literate",1) < 200 )
			return ("就你这点学识，如何能懂得开天辟地？");
		if( me->query_skill("sanban-axe",1) < 200 )
			return ("你斧子用的不够撒熟练！");
		if( me->query_skill("lengquan-force",1) < 200 )
			return ("你内功太低！");
	}
	if(me->query("kai_known")==1)
	{
		if( me->query_skill("literate",1) < 250 )
			return ("要进一步领会开天辟地，你这点学识还不够！");
		if( me->query_skill("sanban-axe",1) < 250 )
			return ("你斧子用的不够撒熟练！");
		if( me->query_skill("lengquan-force",1) < 250 )
			return ("你内功太低！");	
	}
	if(me->query("kai_known")==2)
	{
		if( me->query_skill("literate",1) < 300 )
			return ("要进一步领会开天辟地，你这点学识还不够！");
		if( me->query_skill("sanban-axe",1) < 300 )
			return ("你斧子用的不够撒熟练！");
		if( me->query_skill("lengquan-force",1) < 300 )
			return ("你内功太低！");	
	}
	me->set_temp("kai_learn",1);
	command("say 好，望你早日领会到开天辟地的精髓。");
	message_vision(HIW "盘古挥动鬼斧瞬间在$N四周劈出数下，切断了$N和周围世界的联系！\n" NOR, me);
	me->move("/d/jjf/hundun");
	tell_object(me,"你耳边出来盘古的声音：你现在所处的地方就如当初我破开的混沌，好好在里面领悟(lingwu)一下吧！\n");
	return ("开天绝学又要大放光彩了！");
}