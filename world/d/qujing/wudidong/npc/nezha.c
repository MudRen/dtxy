 //sgzl
#include <ansi.h>

inherit NPC;

void create()
{
  set_name("哪吒", ({ "nezha santaizi", "nezha", "santaizi" }));
  set("title", "三坛海会之神");
  create_family("陷空山无底洞", 1, "弟子");
  set("class", "xian");
  set("long", "一位唇红齿白的美少年。\n");
  set("gender", "男性");
  set("age", 16);
  set("attitude", "heroism");
  set("rank_info/respect", "小太子");
  set("rank_info/rude", "乳臭未干的小儿");
  set("per", 40);
  set("str", 30);
  set("cor", 40);
  set("con", 40);
  set("int", 40);
  set("spi", 40);
  set("cps", 40);
  set("kar", 40);
  set("max_kee", 2000);
  set("max_gin", 1800);
  set("max_sen", 3000);
  set("force", 2600);
  set("max_force", 4000);
  set("force_factor", 100);
  set("max_mana", 3000);
  set("mana", 5000);
  set("mana_factor", 120);
  set("combat_exp", 1500000);
  set("daoxing", 2000000);

  set_skill("spells", 180);
  set_skill("dao", 150);
  set_skill("unarmed", 180);
  set_skill("yinfeng-zhua", 180);
  set_skill("dodge", 180);
  set_skill("lingfu-steps", 180);
  set_skill("parry", 180);
  set_skill("force", 180);
  set_skill("huntian-qigong", 180);
  set_skill("blade", 180);
  set_skill("sword", 200);
  set_skill("qixiu-jian", 180);
  map_skill("spells", "dao");
  map_skill("unarmed", "yinfeng-zhua");
  map_skill("parry", "huoyun-qiang");
  map_skill("sword", "qixiu-jian");
  map_skill("dodge", "lingfu-steps");
  map_skill("force", "huntian-qigong");
  setup();
	carry_object("/d/obj/cloth/taijicloth")->wear();
  carry_object("/d/obj/armor/jinjia")->wear();
  carry_object("/d/obj/weapon/sword/qingfeng")->wield();
  if ("/d/obj/fabao/huntian-ling"->in_mud())
    carry_object("/d/obj/fabao/huntian-fake");
  else
    carry_object("/d/obj/fabao/huntian-ling");
  if ("/d/obj/fabao/qiankun-quan"->in_mud())
    carry_object("/d/obj/fabao/qiankun-fake");
  else
    carry_object("/d/obj/fabao/qiankun-quan");
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

void leave()
{
      	object me = this_object(); 
      	object who = me->query("owner");
      	if( me->is_fighting() )
   		return;
   	remove_call_out("leave");
        destruct(this_object());
}


void die ()
{
        object me = this_object();
        object who = me->query("owner");
        if( query_temp("last_damage_from") == who )
        {
        	if( who->query_temp("daojian/lijing") == "begin" )
        	{
        		message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"哪吒"+NOR"：妖怪太厉害了，我先躲一下！\n"NOR,users());
        	}
        }
        load_object("/obj/empty");
        me->move("/obj/empty");
        call_out ("destruct_me",3,me);
}

void destruct_me (object me)
{
  destruct (me);
}

void unconcious()
{
   die();
}
int accept_fight(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开，小心我打你。\n"NOR,me);
	 	return 0;
	}
}
int accept_kill(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开，小心我打你。\n"NOR,me);
	 	return 0;
	}
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