//Cracked by Roath

inherit NPC;
#include <ansi.h>
void create()
{
	set_name("如来佛祖", ({ "rulai fozu", "rulai", "fo" }));
	set("long", @LONG
如来佛祖。
LONG);
	set("gender", "男性");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "贫僧");
	set("class", "bonze");
	set("family/family_name","南海普陀山");
  	set("str",100);
	set("per",100);//means no rong-mao description.
	set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
	set("force", 4000);
	set("max_force", 2000);
	set("force_factor", 250);
	set("max_mana", 3000);
	set("mana", 6000);
	set("mana_factor", 250);
	set("combat_exp", 2000000);
	set("daoxing", 10000000);

	set_skill("literate", 300);
	set_skill("spells", 300);
	set_skill("buddhism", 300);
	set_skill("unarmed", 300);
	set_skill("jienan-zhi", 300);
	set_skill("dodge", 300);
	set_skill("lotusmove", 300);
	set_skill("parry", 300);
	set_skill("force", 300);
	set_skill("lotusforce", 300);
	set_skill("staff", 300);
	set_skill("lunhui-zhang", 300);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "unarmed", "lingxi" :),
		(: perform_action, "unarmed", "rulai" :),
	}) );

	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	//carry_object("/d/nanhai/obj/nine-ring")->wield();
}

void die()
{
        object guanyin = present("guanyin pusa",environment());
        object who = present(this_object()->query("killer"),environment());
        object hong = present("honghai er",environment());
        if( !who ) return ;
        if( who->query("huohun_known") != 2 ) return ;
        if( guanyin ) guanyin->die();
        message("sound", "\n\n\n如来佛祖怒道：你莫要猖狂，待我以后再来收拾你！\n",environment());
   	message("sound", "\n如来佛祖架起祥云，往西天灵山飞去。。。\n\n",environment());
   	if( objectp(hong) )
   	{
		who->delete_temp("huohun3ask");
   		if( random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
   		{
   			who->add("huohun_known",1);
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗红孩儿(honghai er)：" + who->name() + "助我击败如来、观音，终于领会到了"+HIR"[火魂]"+HIC"的最高境界！\n\n\n"NOR,users());
   		}
   		else
   		{
   			who->set("huohun_cant",1);
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗红孩儿(honghai er)：" + who->name() + "助我击败如来、观音，却未能领悟"+HIR"[火魂]"+HIC"的最高境界，真是可惜！\n\n\n"NOR,users());
   		}
   	}
	destruct(this_object());
}
void unconcious()
{
	die();
}
