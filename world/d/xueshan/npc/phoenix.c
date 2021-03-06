// tomcat
#include <ansi.h>
inherit NPC;
string ask_piaoxue();
void create()
{
	set_name(HIY"凤"HIM"凰"HIC"明王"NOR, ({"fenghuang mingwang", "fenghuang", "mingwang", "wang"}));
	//set("gender", "男性" );
	set("age", 45);
	set("per", 100);
	set("str", 100);
	set("kar",40);
	set("long", "他就是百鸟之王－凤凰。");
	set("class", "yaomo");
	set("combat_exp", 100000000);
	set("daoxing", 100000000);

	set("attitude", "peaceful");
	set("family/family_name","大雪山");
	set_skill("unarmed", 1000);
	set_skill("cuixin-zhang", 1000);
        set_skill("dodge", 1000);
	set_skill("xiaoyaoyou", 1000);
	set_skill("parry", 1000);
        set_skill("sword", 1000);
        set_skill("bainiao-jian", 1000);
	set_skill("blade", 1000);
	set_skill("bingpo-blade", 1000);
	set_skill("throwing", 1000);
        set_skill("force", 1000);   
	set_skill("ningxie-force", 1000);
        set_skill("literate", 1000);
	set_skill("spells", 1000);
	set_skill("dengxian-dafa", 1000);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("parry", "bainiao-jian");
	map_skill("throwing", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	set("piaoxue_known",3);
	set("max_kee", 100000);
	set("max_sen", 100000);
	set("force", 30000);
	set("max_force", 15000);
	set("mana", 30000);
	set("max_mana", 15000);	
	set("force_factor", 250);
	set("mana_factor", 751);
	set_temp("apply/armor",1000);
	set_temp("apply/damage",500);
	set_temp("apply/attack",250);
	set("inquiry",([
      		"飘雪九式": (: ask_piaoxue :),
      		]));
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: cast_spell, "niepan" :), 
        	(: perform_action, "blade", "piaoxue" :),
                (: cast_spell, "juanbi" :),

       }) );
	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("/d/obj/weapon/blade/handudao-redblue")->wield();
}

void init()
{
        object ob = this_player();
        message_vision(HIR"$N的眼前一片火红，一股铺天盖地的气势向$N涌来！\n"NOR,ob);
        if( !ob->query_temp("meet") )
        {
        	ob->set_temp("meet",1);
        	ob->unconcious();
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
        if( me->query("piaoxue_known") < 2 )
      		return ("我的功夫对你来说还是太深奥了，你先去找我弟弟吧！");
        if(me->query("piaoxue_cant"))
      		return ("可惜，可惜啊，你无缘学我一身绝学！");
	if( me->query_skill("ningxie-force",1) < 300 )
		return ("你凝血神功太低，强练绝学对身体有害！");
	if( me->query_skill("bingpo-blade",1) < 300 )
		return ("你冰魄寒刀太低，强练绝学对身体有害！");
	if( me->query_skill("dengxian-dafa",1) < 300 )
		return ("你登仙大法太低，强练绝学对身体有害！");
	if( me->query_temp("piaoxue1/lingwu") == 1 )
		return ("还是安心领悟吧！");
	me->start_busy(20);
	command("say 嗯，看来我这两个孩儿眼光不错，收的好弟子。");
	command("say 孔雀也算顿悟了，只是时日太短，还不能悟出我武学的精要，既然今日有缘，我就教你一点。");
	message_vision(HIC"\n$N仔细听着$n的讲解，不禁喜形于色，对雪山的武功有了更深的体会！\n" NOR, me,this_object());
	message_vision(HIC"\n$N慢慢沉浸入武学的宽广世界，渐渐浑然忘我！\n\n" NOR, me,this_object());
	me->set_temp("piaoxue1/lingwu",1);
	call_out("check",10,me);
	return ("不错，有点悟性！");
}

void check(object me)
{
	me->delete_temp("piaoxue1/lingwu");
	message_vision(HIC"\n$N觉得元神渐渐离开身体，升到半空中，俯瞰着一切！\n" NOR, me);
	message_vision(HIC"\n$N看着漫天飞雪中的春色，遍地玄冰中的奇花。\n" NOR, me);
	message_vision(HIC"\n$N再向凤凰明王看去，却发现凤凰明王再不单纯是一团烈火。\n" NOR, me);
	message_vision(HIC"\n凤凰明王的力量竟然出奇的温和。\n" NOR, me);
	if( random(me->query("int")) > 30 - random( me->query("lunhui_zhuanshi") ) )
	{
		me->add("piaoxue_known",1);
		message_vision(HIC"\n$N豁然明白了，顿悟了阴阳的至理！\n" NOR, me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗凤凰明王(fenghuang mingwang)：" + me->name() + "悟性过人，在我的指导下顿悟阴阳，终于完全掌握了"+HIW"[飘雪九式]"+HIC"！\n\n\n"NOR,users());
	}
	else
	{
		me->set("piaoxue_cant",1);
		message_vision(HIC"\n$N想破了脑袋也没想明白，心中一急，清醒了过来！\n" NOR, me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗凤凰明王(fenghuang mingwang)：" + me->name() + "听了我的知道，可惜悟性不够，未能掌握"+HIW"[飘雪九式]"+HIC"的全部威力！\n\n\n"NOR,users());
	}
	return;
}