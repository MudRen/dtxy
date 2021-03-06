// tomcat
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_piaoxue();
void create()
{
	set_name("孔雀大明王", ({"kongque mingwang", "kongque", "mingwang", "wang"}));
	set("title",  HIG"佛母孔雀大明王菩萨"NOR);
	set("gender", "男性" );
	set("age", 45);
	set("per", 30);
	set("str", 30);
	set("long", "凤凰之长子，于雪山为如来所擒，困于灵山，武功尽失。");
	set("class", "yaomo");
	set("combat_exp", 5200000);

	set("attitude", "peaceful");
	create_family("大雪山", 1, "祖师");
//	set("rank_info/respect", "佛母");
	set_skill("unarmed", 300);
	set_skill("cuixin-zhang", 300);
        set_skill("dodge", 300);
	set_skill("xiaoyaoyou", 300);
	set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("bainiao-jian", 300);
	set_skill("blade", 300);
	set_skill("bingpo-blade", 300);
	set_skill("throwing", 300);
        set_skill("force", 300);   
	set_skill("ningxie-force", 300);
        set_skill("literate", 300);
	set_skill("spells", 300);
	set_skill("dengxian-dafa", 300);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");

	set("max_kee", 3500);
	set("max_sen", 3500);
	set("force", 3500);
	set("max_force", 3500);
	set("mana", 4000);
	set("max_mana", 2000);	
	set("force_factor", 120);
	set("mana_factor", 100);
	set("inquiry",([
      		"飘雪九式": (: ask_piaoxue :),
      		]));

	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("/d/obj/weapon/blade/iceblade")->wield();
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("class")=="bonze" && (string)ob->query("gender")=="男性"  )
	{
		command("kick " + ob->query("id"));
		command("say 快走，快走！我一看到和尚就有气。\n");
		return;
	}

       if (ob->query("obstacle/number") < 26) {
	command("say 这位" + RANK_D->query_respect(ob) + "拜我为师，要先先历尽取经劫难！\n");
	command("sigh");
	return;
	}
	if( (string)ob->query("family/family_name")=="大雪山" ){
		if( (int)ob->query("family/generation") > 2   ){
			command("say 你不是我弟弟的徒弟，本王不收。\n");
		}
		else {
			if( (int)ob->query("daoxing")+(int)ob->query("combat_exp") >= 1000000 ){
				command("nod ");
				command("say 好，" + RANK_D->query_respect(ob) + "好好跟我干，将来大有可为！\n");
				command("recruit " + ob->query("id") );
			}
			else {
				command("say 你还是找到我弟弟吧。\n");
			}
		}
	}

	else{
		command("hmm");
		command("say 这位" + RANK_D->query_respect(ob) + "，在本门可没有一步登天的事。\n");
	}

	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
    ob->set("title", HBWHT"孔雀明王座下寒冰使"NOR);
}

void init()
{       
	object ob=this_player();

	::init();
	if ( ((string)ob->query("gender")=="男性") && ((string)ob->query("class")=="bonze") && (random(3) > 1) )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	
	switch( random(1) ) {
		case 0:
			command("kick " + ob->query("id"));
			command("say 死贼秃！");
			break;
	}
}

string ask_piaoxue()
{
	object book;
	object me=this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法领会我雪山绝学。\n");
	if(me->query("family/family_name") != "大雪山" )
                return ("你不是我大雪山弟子!!\n");
        if( me->query("piaoxue_known") == 3 )
      		return ("雪山绝学，你已经全部掌握了！");
        if( !me->query("piaoxue_known") )
      		return ("我的功夫对你来说还是太深奥了，你先去找我弟弟吧！");
        if(me->query("piaoxue_cant"))
      		return ("可惜，可惜啊，你无缘学我一身绝学！");
        if( me->query("piaoxue_known") == 2 )
      		return ("我这里没有能教你的了，据说凤凰明王重临人间，正在大雪山山顶修炼，你去试试你的运气吧！");
	if( me->query_skill("ningxie-force",1) < 200 )
		return ("你凝血神功太低，强练绝学对身体有害！");
	if( me->query_skill("bingpo-blade",1) < 200 )
		return ("你冰魄寒刀太低，强练绝学对身体有害！");
	if( me->query_skill("dengxian-dafa",1) < 200 )
		return ("你登仙大法太低，强练绝学对身体有害！");
	if( me->query_temp("piaoxue1/jingang") == 1 )
		return ("你去雪山灵鹫洞找他们练练吧！");
	command("say 好，我大雪山后继有人啊。");
	command("say 我被如来抓来，每日里听这些和尚念经，天长日久，竟然也悟到了一些东西。");
	command("say 虽然没有练成什么佛家功法，但是相互借鉴之下，我对凤凰明王传下的武功理解更加深刻了。");
	command("say 凤凰本是火之精华，明王却传下冰魄寒刀等武学，当初我大惑不解，现在我明白一些了。");
	command("say 我现在就把自己的心得体会传授给你。");
	message_vision(HIC"\n$N仔细听着$n的讲解，不禁喜形于色，对雪山的武功有了更深的体会！\n\n" NOR, me,this_object());
	command("say 看来你有所领悟，前些日子我听如来吩咐几个金刚去看守雪山灵鹫洞的什么佛印。");
	me->set_temp("piaoxue1/jingang",1);
	return ("虽然我已没了当年的怨气，不过还想请你帮我出一口恶气，去把哪个佛印给解开（jie）吧！");
}