// by happ@YSZZ
 
inherit NPC;
#include "star.h"
 
void create()
{
        set_name("��³�ϰ�", ({"aldebaran", "jin niu"}));
        set("long", "��ţ�����������׺��Ļƽ�ʥ��ʿ������������ʽ����Ķ��ִ�ܣ�
ڤ��֮ս�У���ذ�����±�ͬ���ھ���\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",30);
        set("per",20);
        set("str",30);
        set("int",35);
        set("combat_exp",1000000);
          set("daoxing",2800000);
        set("chat_chance",20);
        set("chat_msg", ({
                "��³�ϰ�˵������֪��ʱ���ټ����ŵ��ȣ�\n"   
        }));
        set_skill("dodge", 250);
        set("attitude", "friendly");
        set_skill("force", 250);
        set_skill("parry", 250);
        set_skill("unarmed", 250);
        set_skill("sword", 250);
        set_skill("westsword",250);
        set_skill("boxing",250);
        set_skill("balei",250);
        set_skill("spells",250);
        set_skill("jinniu", 250);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","jinniu");
        map_skill("dodge","balei");
        set("max_force", 3000);
        set("force", 7000);
        set("max_mana",5000);
        set("mana",8000);
        set("mana_factor",100);
        set("force_factor", 100);
        set("max_kee", 2000);
        set("max_gin", 2000);
        set("max_sen", 2000);

        setup();
        carry_object(__DIR__"obj/jn_cloth")->wear();
        carry_object(__DIR__"obj/westsword")->wield();
}
 
void init()
{
        
        object me=this_player();
		::init();
        
if (me->query_temp("12gong/cike") == "done")
	{
	set_skill("dodge", 300);
        set_skill("force", 300);
        set_skill("parry", 300);
        set_skill("unarmed", 300);
        set_skill("sword", 300);
        set_skill("westsword",300);
        set_skill("boxing",300);
        set_skill("balei",300);
        set_skill("spells",300);
        set_skill("jinniu", 300);
	command("say �ϻ���˵,��������\n");
    kill_ob(me);
    }
}

void check()
{
        object ob=this_object();
        object me=query_temp("my_killer");
        if( ! me ) return ;
   if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }                               

     switch(random(6))
     {        
        case 0:
        {
        message_vision(YEL"$N�ӻ����䣬������$n��������\n",ob,me);


       if(random(3)==0)
                {
              message_vision(YEL"$N�������Ļ�����û��˫�ۣ�\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(YEL"$NҲ������ͣ��ѷ����Ļ����׷״����ڵأ�\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(YEL"$N������[�ƽ�Ұţȭ],$N����һֻ����Ķ�ţ��$n������\n",ob,me);

                if(random(3)==0)

                {
              message_vision(YEL"$N����ţ�ļ��ת�˸��������\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        }
        break;

        case 2:
        {

        message_vision(HIR"$N��$n�������[���ͺŽ�]��\n",ob,me);

                if(random(3)==0)

                {
              message_vision(HIR"$N��������ܣ�����ӭ����ȥ��\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIR"$n��׼$N��ȭ���򣬶㿪��$N�Ĺ��ٹ�����\n"NOR,me,ob);
        }
        break;

  }
        if( random(8) == 5 )

        powerup();

        remove_call_out("check");
        call_out("check",2+random(3));
}
void die()
{

        object ob = query_temp("my_killer");

        if((ob&&ob->query("12gong/baiyang")=="done") && (ob&&ob->query("12gong/jinniu")!="done"))
        {
        ob->start_busy(3);
        if (ob->query_temp("12gong/cike") == "done")
		message("chat",HIY+"���ƽ�ʮ��������³�ϰ�(Aldebaran):"+ob->name()+
        "�Ѿ�ǿ�����ҽ�ţ��!\n"NOR,users());
		if (ob->query_temp("12gong/cike") != "done")
         message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
        "�����˵ڶ�������ţ��!��������ʮ��!\n"NOR,users());
        ob->set("12gong/jinniu","done");
        ob->add("12gong/number",1);
       ob->add("daoxing", 10000);
        tell_object(ob,"��Ӯ����ʮ�����");

        }
       ::die();
}

void unconcious()
{
  die();
}
