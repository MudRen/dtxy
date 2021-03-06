#include <ansi.h>
inherit NPC;

string ask_pozhen();
void create()
{
    set_name(HIW "元始天尊" NOR, ({"yuanshi tianzun", "tianzun", "yuanshi"}));
    set("title", HIR "三清之首" NOR);
    set("long", "三清之首，法力无边。\n");
    set("gender", "男性");
    set("age", 13500);
    set("str", 40);
    set("per", 40);
    set("attitude", "peaceful");
    set("combat_exp", 10000000);
    set("daoxing", 10000000);
    set("eff_kee", 10000);
    set("eff_sen", 10000);
    set("max_kee", 10000);
    set("max_sen", 10000);
    set("sen", 10000);
    set("kee", 10000);
    set("max_force", 10000);
    set("max_mana", 10000);
    set("mana", 10000);
    set("force", 20000);
    set("force_factor",  500);
    set("mana_factor", 500);
    set_skill("dao", 351 );
    set_skill("zhenyuan-force", 351);
    set_skill("spells", 321);
    set_skill("force", 301);
    set_skill("moonshentong", 351);
    set_skill("whip", 301);
    set_skill("staff", 301);
    set_skill("blade", 301);
    set_skill("spear", 301);
    set_skill("hammer", 301);
    set_skill("buddhism", 351);
    set_skill("taiyi", 351);
    set_skill("lotusforce", 351);
    set_skill("wuxiangforce", 351);
    set_skill("xuanzong-force", 351);
    set_skill("yuxu-spells", 351);
    set_skill("moonforce", 351);
    set_skill("stick", 301);
    set_skill("dodge", 301);
    set_skill("unarmed", 301);
    set_skill("parry", 301);
    set_skill("sword", 251);
      map_skill("force", "wuxiangforce");
      map_skill("spells", "dao");
	set("inquiry",([
      "破阵": (: ask_pozhen :),
      ]));
    set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
        (: cast_spell, "light" :),
        (: cast_spell, "thunder" :),
        (: cast_spell, "dingshen" :),
        (: cast_spell, "fenshen" :),
(: exert_function, "jldl" :)
}));
      setup();
   
}

int accept_fight(object me)
{
        write("仙人你也想打？\n");
        return 0;
}

int recognize_apprentice(object me)
{
      object ob = this_player();
      
        if (!(int)ob->query_temp("mark/仙"))
             return notify_fail( HIR "看起来" HIW "元始天尊" HIR "想杀死你！\n"NOR);
        if( ( ob->query("family/family_name") != "方寸山三星洞"
            && ob->query("family/family_name") != "昆仑山玉虚洞"
            && ob->query("family/family_name") != "南海普陀山"
            && ob->query("family/family_name") != "月宫"
            && ob->query("family/family_name") != "五庄观")
            || ob->query("combat_exp")  < 2000000 ) 
             return notify_fail( HIR "看起来" HIW "元始天尊" HIR "想杀死你！\n"NOR);

             ob->add_temp("mark/仙", -1);
               return 1;
}

int accept_object(object me,object ob)
{
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "zhuxian spear" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "juexian blade" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "luxian stick" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "xianxian whip" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/get") > 3 )
       	{
       		me->delete_temp("quzhu/get");
       		me->delete_temp("quzhu/zhuxian");
       		message_vision(HIW"只见$N"+HIW"将四件兵器合炼，又在兵器种融入一朵白莲，耀眼的白光闪过，$N"+HIW"的手上已经多了一把白色长剑！\n"NOR, this_object());
       		if( random(me->query("int")) > 25 - random( me->query("lunhui_zhuanshi") ) )
      		{
      			me->add("quzhu_known",1);
	  		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗元始天尊(yuanshi tianzun)：" + me->name() + "勇闯十绝阵，破四门，夺四宝，助我练成"+HIW"诛仙剑"+HIC"，对"+HIR"[驱神逐魔]"+HIC"领悟加深了！\n\n\n"NOR,users());
      			command("say 如果你要继续解密，再问我破阵之事吧！");
      		}
      		else
      		{
      			me->set("quzhu_cant",1);
	  		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗元始天尊(yuanshi tianzun)：" + me->name() + "勇闯十绝阵，破四门，夺四宝，助我练成"+HIW"诛仙剑"+HIC"，却无法领悟更深的"+HIR"[驱神逐魔]"+HIC"！\n\n\n"NOR,users());
      			command ("say 你莫要伤心，很快就能再次尝试了！");
      		}
       	}
       	return 1;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}
   
string ask_pozhen()
{
	object me=this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法破阵。\n");
	if(me->query("family/family_name") != "昆仑山玉虚洞" )
                return ("你不是我昆仑弟子，无法破阵!!\n");
        if(me->query("quzhu_cant"))
      		return ("你的机缘不够，无法破阵！");
        if( me->query("quzhu_known") > 2 )
      		return ("破阵的法诀你都已经知道了，把机会留给别人吧！");
      	if( me->query_temp("quzhu/mo") && me->query_temp("mark/仙") > 2 )
      	{
      		me->delete_temp("mark");
      		me->delete_temp("quzhu/mo");
      		if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
      		{
      			me->add("quzhu_known",1);
	  		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗元始天尊(yuanshi tianzun)：" + me->name() + "降伏十绝阵中魔物，初步领悟了"+HIR"[驱神逐魔]"+HIC"！\n\n\n"NOR,users());
      			return ("如果你要继续解密，再问我破阵之事吧！");
      		}
      		else
      		{
      			me->set("quzhu_cant",1);
	  		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗元始天尊(yuanshi tianzun)：" + me->name() + "降伏十绝阵中魔物，可惜悟性不够，无法领悟"+HIR"[驱神逐魔]"+HIC"！\n\n\n"NOR,users());
      			return ("你莫要伤心，很快就能再次尝试了！");
      		}
      	}
      	if( !me->query("quzhu_known") )
      	{
		me->set_temp("quzhu/mo",1);
		return ("你先去阵中降伏（xiang）三个魔物，再来找我！");
	}
	else if( me->query("quzhu_known") == 1 )
	{
		me->set_temp("quzhu/zhuxian",1);
		return ("阵中四角分别由风神、水神、火神、雷神镇守着陷仙鞭、绝仙刀、戮仙棍、诛仙枪，你去帮我夺来！");
	}
	else
	{
		me->set_temp("quzhu/ttjz",1);
		return ("现在阵的四角已经陷落，就剩下中心的通天教主了，他是我师弟，我无法亲自出手，就麻烦你了！");
	}
}