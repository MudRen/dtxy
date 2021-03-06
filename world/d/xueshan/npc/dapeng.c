// dapeng.c...weiqi, 97.09.27.

inherit NPC;
inherit F_MASTER;
string ask_piaoxue();
void create()
{
	set_name("大鹏明王", ({"dapeng mingwang", "dapeng", "mingwang", "wang"}));
	set("title", "雪山之祖");
	set("gender", "男性" );
	set("age", 45);
	set("per", 30);
	set("str", 30);
	set("long", "这位大鹏明王的确大有来历，说起来跟佛祖如来也有点亲戚关系，\n算是如来的“舅舅”。他不似其兄孔雀明王作恶多端，却也并非善类，\n且因其兄之故跟佛门结下深仇。生平最讨厌的就是和尚。\n");
	set("class", "yaomo");
	set("combat_exp", 1800000);
	set("daoxing", 3000000);

	set("attitude", "peaceful");
	create_family("大雪山", 1, "祖师");
	set("rank_info/respect", "明王");
	set_skill("unarmed", 200);
	set_skill("cuixin-zhang", 200);
	set_skill("dodge", 200);
	set_skill("xiaoyaoyou", 200);
	set_skill("parry", 200);
	set_skill("sword", 200);
	set_skill("bainiao-jian", 200);
	set_skill("blade", 200);
	set_skill("bingpo-blade", 200);
	set_skill("throwing", 200);
	set_skill("force", 200);   
	set_skill("ningxie-force", 200);
	set_skill("literate", 150);
	set_skill("spells", 200);
	set_skill("dengxian-dafa", 200);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");

	set("max_kee", 3500);
	set("max_sen", 3500);
	set("force", 3500);
	set("max_force", 1800);
	set("mana", 4000);
	set("max_mana", 2000);	
	set("force_factor", 120);
	set("mana_factor", 100);

	set_temp("apply/damage", 50);
	set_temp("spply/armor", 50);
	set_temp("apply/dodge", 50);
	set("inquiry",([
      		"寒毒": (: ask_piaoxue :),
      		]));
       set("chat_chance_combat", 50);
       set("chat_msg_combat", ({
                (: cast_spell, "juanbi" :),
                (: cast_spell, "tuntian" :),
                (: perform_action, "sword", "chaofeng" :),

       }) );
            setup();
	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("d/obj/weapon/sword/qinghong")->wield();
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("class")=="bonze" && (string)ob->query("gender")=="男性"  )
	{
		command("kick " + ob->query("id"));
		command("say 快走，快走！我一看到和尚就有气。\n");
		return;
	}

	if( (string)ob->query("family/family_name")=="大雪山" ){
		if( (int)ob->query("family/generation") > 3   ){
			command("say 没有四大护法的推荐，本王很难考虑。\n");
		}
		else {
			if( (int)ob->query("daoxing")+(int)ob->query("combat_exp") >= 500000 ){
				command("nod ");
				command("say 好，" + RANK_D->query_respect(ob) + "好好跟我干，将来大有可为！\n");
				command("recruit " + ob->query("id") );
			}
			else {
				command("say 你还是找青狮，白象他们先练着吧。\n");
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
        if(me->query("piaoxue_cant"))
      		return ("这个与你无关！");
        if( me->query("piaoxue_known") )
      		return ("我这里没有能教你的了，你去找我兄长吧！");
	if( me->query_skill("ningxie-force",1) < 200 )
		return ("你凝血神功太低，对抗寒毒会危机到生命的！");
	if( me->query("piaoxue/handu") == 1 )
		return ("你先用蓝色冰块试试吧，注意循序渐进！");
	if( me->query("piaoxue/handu") == 2 )
		return ("很好，你再用双色冰块试试吧！");
	command("say 好，近年来我一直在这里潜心钻研克制病毒之法。");
	command("say 唉，结果一个不小心中了寒毒，不过通过这数年来，我以本身内力对抗体内寒毒，也总结出了些经验。");
	command("say 我大雪山历来都用五仙汤来提高凝血神功的修为，通常五仙汤都是用内力凝结玄冰制成。");
	me->set("piaoxue/handu",1);
	return ("你不妨使用蓝色冰块和双色冰块一试，不过一定要小心！");
}