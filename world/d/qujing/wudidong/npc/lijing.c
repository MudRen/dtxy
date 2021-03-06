#include <ansi.h>
inherit NPC;

void create()
{
        set_name("李靖", ({ "li jing", "jing", "li" }) );
	set("gender", "男性" );
	set("long", "托塔李天王乃是天界元帅，麾下十万天兵天将，法力无边。\n");
	set("age",40);
	set("title", "托塔天王");
	set("str", 40);
	set("int", 30);
	set("con", 30);
	set("spi", 30);
	set("per", 30);
	set("class", "xian");
	set("attitude", "heroism");
	set("combat_exp", 4500000);
	set("daoxing", 8000000);
	set("max_kee", 4000);
	set("max_sen", 4000);
	set("force",9000);
	set("max_force",5000);
	set("force_factor", 500);
	set("mana", 9000);
	set("max_mana", 9000);
	set("mana_factor", 550);

	set("eff_dx", 600000);
	set("nkgain", 600);

	set_skill("spells", 280);
        set_skill("dao", 250);
        set_skill("unarmed", 300);
        set_skill("yinfeng-zhua", 250);
        set_skill("dodge", 280);
        set_skill("blade", 280);
        set_skill("kugu-blade", 280);
        set_skill("yaofa", 300);
        set_skill("lingfu-steps", 280);
        set_skill("parry", 280);
        set_skill("force", 280);
        set_skill("huntian-qigong", 280);
//        set_skill("blade", 280);
        set_skill("sword", 300);
        set_skill("qixiu-jian", 280);
        map_skill("spells", "dao");
        map_skill("unarmed", "yinfeng-zhua");
        map_skill("parry", "kugu-blade");
        map_skill("sword", "qixiu-jian");
        map_skill("dodge", "lingfu-steps");
        map_skill("force", "huntian-qigong");
	set("chat_chance_combat", 60);
   
   set("chat_msg_combat", ({
        (: perform_action,"sword", "yaowu" :),
        (: perform_action,"unarmed", "duzun" :),
   }) );
        create_family("陷空山无底洞", 1, "弟子");
        setup();
        carry_object("/d/obj/fabao/huangjin-baota");
	carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/sky/obj/zhanyaojian")->wield();
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");        

}

void init()
{
    
    ::init();
    call_out("leave",180);
    
}
int accept_fight(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开。\n"NOR,me);
	 	return 0;
	}
}
int accept_kill(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开。\n"NOR,me);
	 	return 0;
	}
}
void leave()
{
      	object me = this_object(); 
      	object who = me->query("owner");
      	if( me->is_fighting() )
   		return;
   	remove_call_out("leave");
        destruct(this_object());
}

void destruct_me (object me)
{
  destruct (me);
}

void unconcious()
{
   die();
}


void die ()
{
        object swk;
        object nezha;
        object me = this_object();
        object who = me->query("owner");
        swk = present("sun xingzhe",environment());
        nezha = present("nezha santaizi",environment());
        if( swk ) swk->die();
        if( nezha ) nezha->die();
        if( query_temp("last_damage_from") == who )
        {
        	who->set_temp("daojian/lijing","done");
	        message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：妖怪太厉害了！李靖架起彩云上天找人帮忙去了！\n"NOR,users());
	        message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"："+who->name()+"做的好，终于打败了李靖他们，玉成了我何唐僧的好事，快些进洞来！\n"NOR,users());
	        message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+who->name()+NOR"：是，夫人！"+who->name()+"使了个土遁，进了无底洞！\n"NOR,users());
	        who->move("/d/qujing/wudidong/inner-tang");
        }
        load_object("/obj/empty");
        me->move("/obj/empty");
        call_out ("destruct_me",3,me);
}


void heart_beat()
{
        if (!query_temp("weapon") && !query_temp("added"))
        {
	        set_temp("added", 1);
	        set("force_factor",100);
	        set("force",5000);
        }
        if (query("eff_kee")<query("max_kee"))
        {
	        command("eat yao");
		command("exert recover");
	}
	else
	{
	 	command("surrender");
		command("exert recover");
	}
        ::heart_beat();
}
