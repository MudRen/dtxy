 //sgzl
#include <ansi.h>

inherit NPC;

void create()
{
  set_name(HIW"��˽�"NOR,({"zhu bajie","zhu","bajie"}));
  set("gender", "����");
  set("title", HIY"��ͽ��"NOR);
  set("age", 35);
  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 2000000);
  set("daoxing", 2000000);
  set("kee", 2600);
  set("max_kee", 2600);
  set("sen", 2800);
  set("max_sen", 2800);
  set("force", 7000);
  set("max_force", 3500);
  set("mana", 7000);
  set("max_mana", 3500);
  set("force_factor", 40);
  set("mana_factor", 40);
  set("str", 40);
  set("per", 10);

  set_skill("unarmed", 200+random(50));
  set_skill("dodge", 200+random(50));
  set_skill("parry", 200+random(50));
  set_skill("rake", 200+random(50));
  set_skill("force", 200+random(50));
  set_skill("spells", 200+random(50));
  set_skill("baguazhou", 200+random(50));
  set_skill("yanxing-steps", 200+random(50));
  set_skill("skyriver-rake", 200+random(50));
  map_skill("force", "lengquan-force");
  map_skill("spells", "baguazhou");
  map_skill("rake", "skyriver-rake");
  map_skill("parry", "skyriver-rake");
  map_skill("dodge", "yanxing-steps");
  
  set_temp("apply/attack", 200);
  set_temp("apply/defense", 200);
  set_temp("apply/armor", 200);
  set_temp("apply/damage", 200);  
  set("force_factor",300);
  set("mana_factor",300);
  set("bellicosity",300);
  set("nk_gain", 100+random(50));
  set("nk_factor", 12);
  
   setup();
        carry_object("/d/kaifeng/obj/jiuchipa")->wield();
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
   	message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�˽�"+NOR"��ʦ��û�����֣�������·�ɣ�ʦͽ���˴Ҵ��������ȥ��\n"NOR,users());
   	if( who )
   		who->set_temp("daojian/zbj","fail");
   	remove_call_out("leave");
        destruct(this_object());
}

void die ()
{
        object me = this_object();
        object who = me->query("owner");
        if( query_temp("last_damage_from") == who )
        {
        	who->set_temp("daojian/zbj","done");	
        	message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"��"+who->name()+"���ĺã������˽�ץ��������\n"NOR,users());
        	message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+who->name()+NOR"���ǣ����ˣ�"+who->name()+"ץ����˽䣬ʹ�˸����ݣ������޵׶���\n"NOR,users());
        	message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"��С���ǣ�����˽俴���ˣ���˽䱻��С��̧�Ž����ڶ���\n"NOR,users());
        	who->move("/d/qujing/wudidong/inner-tang");
        }
        else
        {
        	message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�˽�"+NOR"��ʦ�������ֺ���������˽�ܿ�����˰�æȥ�ˣ�\n"NOR,users());
        	if( who )
   			who->set_temp("daojian/zbj","fail");
        }
        load_object("/obj/empty");
        me->move("/obj/empty");
        call_out ("destruct_me",3,me);
  
}

void destruct_me (object me)
{
  	destruct(me);
}

int accept_fight(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N˵�������߿������������үү��\n"NOR,me);
	 	return 0;
	}
}
int accept_kill(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N˵�������߿������������үү��\n"NOR,me);
	 	return 0;
	}
}
void unconcious()
{
   	die();
}

void heart_beat()
{
        if (!query_temp("weapon") && !query_temp("added"))
        {
	        set_temp("added", 1);
	        set("force_factor",100);
	        set("force",2000);
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