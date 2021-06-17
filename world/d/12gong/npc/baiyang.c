inherit NPC;
#include "star.h"
void get_date();
 
void create()
{
        set_name("������", ({"mu"}));
        set("long", "��˵�еİ��򹬻ƽ�սʿ���ػ��Ű�����,�����������ǻ۵Ļƽ�ʥ��ʿ�����ó�����ʥ�¡�
��ʮ����֮ս�У�������ʸ����������߸С�ڤ��֮ս�У�������ǿ��ڤ��ʿ֮һ������
�ǵİͱ�¡�� \n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("attitude", "friendly");
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
          set("combat_exp",7800000);
          set("daoxing",7800000);
        set("chat_chance",20);
        set("chat_msg", ({
                "������˵������֪��ʱ���ټ����ŵ��ȣ�\n"   
        }));
          set_skill("dodge", 250);
          set_skill("force", 250);
          set_skill("parry", 250);
          set_skill("unarmed", 250);
          set_skill("sword", 250);
         set_skill("westsword",250);
  //        set_skill("huangjin-step",250);
		  set_skill("balei",250);
		  set_skill("boxing",250);
         
        set_skill("baiyang", 350);
        map_skill("sword","westsword");
		map_skill("parry","westsword");
		map_skill("dodge","balei");
        map_skill("unarmed","boxing");
        map_skill("spells","baiyang");
         set("max_force", 2000);
         set("force", 4000);
         set("max_mana",3000);
         set("mana",6000);
         set("mana_factor",50);
         set("force_factor", 50);
       set("max_kee", 2000);
       set("max_gin", 2000);
        set("max_sen", 2000);

        setup();
        carry_object(__DIR__"obj/by_cloth")->wear();
        carry_object(__DIR__"obj/westsword")->wield();
}
 

void init()
{
        
        object me=this_player();
		::init();
        if (me->query_temp("12gong/cike") != "done")
			{
				
				
				remove_call_out("greeting");
                call_out("greeting", 3, me);
        }
if (me->query_temp("12gong/cike") == "done")
	{
	command("say �ô�ĵ���,��������ɱ[Ů��] �ŵ���,�ȹ�����һ�أ�\n");
    kill_ob(me);
    }
}



void check()
{
        object ob=this_object();
        object me=query_temp("my_killer");
    
     if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }
     if( me->is_ghost() )
     {
     remove_call_out("check");
     return;
     }
      
     switch(random(6))
     {        
        case 0:
        {
        message_vision(HIR"$N˫��һ�ӣ�һ���һ�ֱ��$n��ȥ��\n",ob,me);

        if(random(2))
        
                {
              message_vision(HIR"$N��$n���һ��ո���ͷ������\n"NOR,me,ob);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(HIR"$N����׾ٵĶ����$n�Ĺ�����\n"NOR,me,ob);
        }
        break;


        case 1:
        {

        message_vision(HIR"$N�������ѣ���ʱһֻ������$nֱ���ȥ��\n",ob,me);

        if(random(2))

                {
              message_vision(HIR"$N������ײ�˸���������\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIR"$N���Ű�����һ����ͣ������ԹԴ��Ա��￪�ˣ�\n"NOR,me);
        }
        break;

        case 2:
        {

        message_vision(HIR"$N����[��м��ת��],�ƽ�������$n \n",ob,me);

        if(random(2))

                {
              message_vision(HIR"$N��[��м��ת��]����,��ʱѪ����ע�����Ⱦ����ȫ��\n"NOR,me);
              me->add("eff_kee",-3*query("max_kee")/10);
              me->add("eff_sen",-3*query("max_sen")/10);
                }
        else
        message_vision(HIR"$N��׼�ƽ����ķ�������Ծ�𣬶��������һ����\n"NOR,me);
        }
        break;

  }
 //       if( present(me,environment()) )  return ;

        if( random(8) == 5 )
        powerup();

        remove_call_out("check");
        call_out("check",2+random(3));
}
void die()
{

        object ob = query_temp("my_killer");
        
        if(ob&&ob->query("12gong/baiyang")!="done")
        {
        ob->start_busy(3);
        message("chat",HIY+"���ƽ�ʮ������������(Mu):"+ob->name()+
        "ǿ���Ұ���,����Ҫ��ɱŮ���ŵ���,���ȫ����ס��!\n"NOR,users());
        ob->set("12gong/baiyang","done");
        ob->add("12gong/number",1);
         ob->add("combat_exp", 10000);
        tell_object(ob,"��Ӯ����ʮ�����");
        
        }
       ::die();
}


void greeting(object me)
{
     if( !me || !visible(me) || environment(me) != environment() ) return;
     if(!me->query("12gong/baiyang")) 
	{command("say " + "Ŭ��ȥս����,���С������ս���н��õ�����,����Ļƽ�ʥ��ʿ��ͬ��\n"+
		 "���������Щ��������,�������������С���汬����˲������ս����,����ҪС��.�ҿ���\n"+
		 "ֻ�ܰ��������Ŀ��׷�������,Ҫȡ�ûƽ�ʥ��,�Լ�ȥ֤���Լ���������!\n");
	 me->add_temp("apply/armor",100);
	 message("chat",HIY+"\n\n���ƽ�ʮ�������ŵ���(Athena):"+me->name()+
        "ͨ�����򹬽�������ʮ��!\n\n"NOR,users());
	 me->set("12gong/baiyang","done");
        me->add("12gong/number",1);
   me->add("daoxing", 10000);
        tell_object(me,"��Ŀ��׷�������ǿ��\n");
		tell_object(me,"��Ӯ����ʮ�����\n");
	    
	}
    
	 me->move("/d/12gong/by2jn1"); 
     tell_object(me,"�㱻�������������ͳ��˰���!\n");
}

void unconcious()
{
  die();
}
