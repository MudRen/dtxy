#include <ansi.h>
inherit NPC;

void create()
{
        set_name("�", ({ "li jing", "jing", "li" }) );
	set("gender", "����" );
	set("long", "�����������������Ԫ˧������ʮ������콫�������ޱߡ�\n");
	set("age",40);
	set("title", "��������");
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
        create_family("�ݿ�ɽ�޵׶�", 1, "����");
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
		message_vision(CYN"$N˵�������߿���\n"NOR,me);
	 	return 0;
	}
}
int accept_kill(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N˵�������߿���\n"NOR,me);
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
	        message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"������̫�����ˣ����������������˰�æȥ�ˣ�\n"NOR,users());
	        message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"��"+who->name()+"���ĺã����ڴ��������ǣ�������Һ���ɮ�ĺ��£���Щ��������\n"NOR,users());
	        message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+who->name()+NOR"���ǣ����ˣ�"+who->name()+"ʹ�˸����ݣ������޵׶���\n"NOR,users());
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
