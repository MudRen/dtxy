// honghaier.c 红孩儿
// By Dream Dec. 20, 1996
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_huohun();
string ask_fmtd();
void create()
{
	set_name("红孩儿", ({ "honghai er" }));
	set("title", "南海观音之徒");   
	set("long", @LONG
他本是牛魔王之子，生性好斗；后被南海观音收服，脾气却不见有什么好转。
他使得一手的好枪法，火云枪更是鲜有敌手，寻常人是不敢碰他的。
LONG);
	set("gender", "男性");
	set("age", 15);
	set("attitude", "heroism");
	set("max_kee", 750);
	set("max_gin", 600);
	set("max_sen", 750);
	set("force", 450);
	set("max_force", 300);
	set("force_factor", 20);
	set("max_mana", 350);
	set("mana", 500);
	set("mana_factor", 50);
	set("combat_exp", 240000);
	set("daoxing", 400000);

	set_skill("literate", 80);
	set_skill("spells", 100);
	set_skill("buddhism", 100);
	set_skill("unarmed", 60);
	set_skill("jienan-zhi", 60);
	set_skill("dodge", 80);
	set_skill("lotusmove", 80);
	set_skill("parry", 80);
	set_skill("force", 80);
	set_skill("lotusforce", 70);
	set_skill("staff", 50);
	set_skill("lunhui-zhang", 40);
	set_skill("spear", 300);
	set_skill("huoyun-qiang", 300);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "huoyun-qiang");
	map_skill("staff", "lunhui-zhang");
	map_skill("spear", "huoyun-qiang");
	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
		(: cast_spell, "jingang" :),
	}) );
	set("inquiry",([
      		"leave"    : (: ask_huohun :),
      		"佛魔"    : (: ask_fmtd :),
      			]));
	create_family("南海普陀山", 2, "弟子");

	setup();
	carry_object("/d/nanhai/obj/huojianqiang")->wield();
        carry_object("/d/qujing/bibotan/obj/zhanpao")->wear();
}

void attempt_apprentice(object ob)
{
	if (((int)ob->query_skill("buddhism", 1) < 50 )) {
		command("say " + RANK_D->query_respect(ob) + "的佛法修行还不精，还需多加努力才是！");
		return;
	}
	command("smile");
	command("say 很好，我就收下你，希望你多加努力，早成正果。\n");

	command("recruit " + ob->query("id") );
	message("system", HIY"我佛门又多了一个弟子  "+this_player()->name()+HIW"
                 南海普陀山的势力加强了。\n"NOR,users());
	return;
}

int ask_huohun()
{
	object me = this_player();
	object guanyin;
	if( me->query_temp("huohun/zhenshen") )	
	{
		command("say 我也想回去啊，不过现在时机不对！");
		if( !objectp( guanyin = present("guanyin pusa",environment())) )
		{
			guanyin = new("/d/nanhai/npc/guanyin");
			guanyin->move(environment(me));
			message_vision(HIY"\n空中出来观音菩萨的声音：谁在此扰乱佛家净地？！\n",me);
			message_vision(HIY"\n观音菩萨架着祥云飞了过来！\n",me);
		}
		message_vision(HIR"\n观音菩萨一摆手中九环锡杖，拦住了你！\n",me);
		guanyin->kill_ob(me);
		return 1;
	}
	else
		return 0;
}

string ask_fmtd()
{
	object me = this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法领会佛魔同道绝学。\n");
	if(me->query("family/family_name") != "南海普陀山" )
                return ("你不是我普陀弟子!!\n");
        if(me->query("fmtd_cant"))
      		return ("你无法领悟更高的佛魔同道！");
        if(me->query("fmtd_known") > 1 )
      		return ("佛魔同道的口诀你都已经知道了啊！");
      	if( me->query_skill("literate",1) < 200 )
		return ("你这点学识不足以领悟佛魔同道！");
	if( me->query_skill("huoyun-qiang",1) < 200 )
		return ("你这点枪法不足以领悟佛魔同道！");
	if( me->query_skill("lotusforce",1) < 200 )
		return ("你这点内功不足以领悟佛魔同道！");	
      	command("sigh");
      	if( me->query_temp("fmtd/zhenshen") == 1 )
      	{
      		command("say 我等你的好消息！");
      	}
      	else if( !me->query("fmtd_known") )
      	{
		me->set_temp("fmtd/zhenshen",1);
		command("say 我近来修行，对佛魔之道有所领悟，奈何我魔力太弱，无法更进一步。");
		command("say 如果你能帮我去火云洞取来五行车，我可以借五行车之力，加深修炼。");
		command("say 到时如果有所成就，你我一同分享。");
		command("say 对了，你只需将五行洞中的小车取来给我就可以了！");
	}
	else
	{
		message_vision(HIY"\n突然间佛光大盛，让人睁不开眼睛。\n"NOR,me);
		command("say 佛祖已经知道了，请你去金顶参悟大道！");
		me->set_temp("fmtd/canwu",1);
		message_vision("佛光中伸出一只巨大的佛手轻轻托起$N向远方伸去……\n",me);
		me->move("/d/southern/emei/jinding");
		message_vision("佛手轻轻一翻，$N从里面跳出来，已经置身峨嵋金顶。\n",me);
	}
	return ("加油，加油！");
}

int accept_object(object me, object ob)
{
  	if( me->query_temp("fmtd/zhenshen") == 1 && me->query_temp("fmtd/num") < 5 )
	{	 
	 	if( ob->query("id") == "che" && ob->query("owner") == me->query("id") )
		{
	 		command ("nod "+me->query("id"));
      			me->add_temp("fmtd/num",1);
      			call_out("destroy", 2, ob);
		}
		if( me->query_temp("fmtd/num") == 5 )
		{
			message_vision(HIC"$N将五行车按照五行的方位摆好，足下莲光一现，飘在了五行车的正上方。\n"NOR,this_object());
			command("say 你仔细观看我行功的方法，我先修炼了，一会再指点于你！");
			message_vision(HIC"$N盘膝而坐，身下一朵白莲闪闪发光，与五行车相互辉映。\n"NOR,this_object());
			message_vision(HIC"$n见$N已经开始修炼，连忙凝神屏息，仔细观摩学习。\n"NOR,this_object(),me);
			message_vision(HIC"$N越看越是入迷，渐渐忘记了时间。\n"NOR,me);
			me->start_busy(15);
			call_out("xiulian_finish",10,me,this_object());
		}
		return 1;
	}
	return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

void xiulian_finish( object me, object who )
{
	if( !me || !who )
		return;
	message_vision(HIC"$N觉得有人推了你一下，渐渐回过神来。\n"NOR,me);
	message_vision(HIC"只见$N正在看着$n，而$N面上神光内敛，显然修为大有长进。\n"NOR,this_object(),me);
	command("say 我看你若有所悟，刚才借五行车的魔力，我对佛魔之道的领悟加深了一些，这就与你分享！");
	message_vision(HIC"$N在$n耳边说出了一段深奥的口诀。\n"NOR,this_object(),me);
	message_vision(HIC"$N盘膝静坐，开始参悟$n刚刚告诉$N的口诀。\n"NOR,me,this_object());
	me->start_busy(15);
	if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
		call_out("finish1",10,me);
	else
		call_out("finish2",10,me);
	return;
}

void finish1( object me )
{
	message_vision(HIC"$N面色一会红，一会金，甚是奇怪。\n" NOR,me);
	message_vision(HIC"$N面色慢慢变得缓和，似乎要发出如明珠般的光泽！\n" NOR,me);
	message_vision(HIC"$N缓缓收功，站立起来，向红孩儿深深鞠躬！\n" NOR,me);
	me->delete_temp("fmtd");
	me->add("fmtd_known",1);
	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗红孩儿(hong haier)：" + me->name() + "助我寻回五行车，领悟了"+HIB"[佛魔同道]"+HIC"绝学！\n\n\n"NOR,users());
	command("say 这只是佛魔同道的基本功，如果日后有所领悟再来找我！");
	return ;
}

void finish2( object me )
{
	message_vision(HIC"$N面色一会红，一会金，甚是奇怪。\n" NOR,me);
	message_vision(HIC"$N突然面露痛苦之色，好像叉了内息！\n" NOR,me);
	message_vision(HIR"$N缓缓收功，站立起来，面色灰败，竟是无法领悟红孩儿告诉$N的口诀！\n" NOR,me);
	me->delete_temp("fmtd");
	me->set("fmtd_cant",1);
	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗红孩儿(hong haier)：" + me->name() + "助我寻回五行车，可惜悟性不够，无法领悟"+HIB"[佛魔同道]"+HIC"绝学！\n\n\n"NOR,users());
	command("sigh " + me->query("id"));
	command("say 你悟性不足，莫要强求，佛门武功博大精深，足够你学的了！");
	return ;
}