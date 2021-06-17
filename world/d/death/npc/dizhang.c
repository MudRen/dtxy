
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
//puti.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string avenge();
string ask_chuxian();
string ask_cancel();
int begin_go();

void create()
{
  set_name("�ز�������", ({"dizang pusa", "pusa"}));
  set("long", "�������񣬴�����磬һ���ྲ��
�������������ܵظ������¹��ĵز���������\n");
  set("gender", "����");
  set("class", "youling");
  set("age", 70);
  set("attitude", "friendly");
  set("shen_type", 1);
  set("per", 30);
  set("str", 30);
  set("int", 30+random(5));
  set("nkgain",790);
  set("max_kee", 3000);
  set("max_gin", 2500);
  set("max_sen", 2000);

  set("force", 4500);
  set("max_force", 4000);
  set("force_factor", 200);
  set("max_mana", 5500);
  set("mana", 8000);
  set("mana_factor", 200);

  set("combat_exp", 2000000);

//   set_skill("unarmed", 150);
   set_skill("unarmed", 200);
  set_skill("whip", 200);
  set_skill("hellfire-whip", 200);
  set_skill("dodge", 200);
//   set_skill("parry", 150);
   set_skill("parry", 200);
//   set_skill("literate", 130);
   set_skill("literate", 200);
//   set_skill("spells", 180);
   set_skill("spells", 200);
  set_skill("force", 200);
//  set_skill("tonsillit", 180);
  set_skill("tonsillit", 200);
  set_skill("ghost-steps", 200);
//     set_skill("gouhunshu", 190);
     set_skill("gouhunshu", 200);
//   set_skill("jinghun-zhang", 150);
   set_skill("jinghun-zhang", 200);
  set_skill("kusang-bang", 200);
   set_skill("zhuihun-sword", 200);
   set_skill("sword", 200);
   set_skill("stick", 200);

  map_skill("force", "tonsillit");
  map_skill("unarmed", "jinghun-zhang");
  map_skill("dodge", "ghost-steps");
  map_skill("spells", "gouhunshu");
  map_skill("parry", "hellfire-whip");
  map_skill("whip", "hellfire-whip");
   map_skill("sword", "zhuihun-sword");
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "whip","three" :),
                (: exert_function, "recover" :),
                (: cast_spell, "gouhun" :),
        }) );
  set("nk_gain", 600);
set("inquiry",([
  "�л�": (: ask_chuxian :),
  "��̨����": (: begin_go :),
  "cancel": (: ask_cancel :),
  "����": (: avenge :) ]));
   
  set_temp("apply/armor", 50);
  set_temp("apply/dodge", 50);

  
  create_family("���޵ظ�", 1, "���");
  setup();
  
  carry_object("/d/obj/cloth/baipao")->wear();
  carry_object("/d/obj/weapon/whip/longsuo")->wield();
}

string avenge()
{
    object who=this_player(),killer,where;
    string killid;
    if((string)who->query("family/family_name")!="���޵ظ�")
        return ("�㲻�Ǳ��ɵ��ӣ������뱾���θɣ�");
    if(who->query("faith")<1000)
        return ("���ڱ���������������������Ŭ�����С�");
    if(who->query("avenge/mud_age")>=who->query("death/mud_age"))
        return ("����δ����Ѷ");
    killid=who->query("kill/last_killer");
    killer=find_living(killid);
    if(!killer||!userp(killer))
        return ("��������������һ��");
    command("say �������ȥΪ�㱧��");
    who->set("avenge/mud_age",who->query("mud_age"));
    where=environment(who);
    tell_room(where,"ֻ���ز������������һָ��\n");
    tell_room(where,"����С����ڣ���ȥ��"+killer->query("name")+"ץ����\n")
;
    tell_room(environment(killer),"�������һֻ���ֽ�"+killer->query("name")
+"ץ��������");
    killer->move(where);
    tell_room(where,killer->query("name")+"���ӿ�������������\n");
    command("say ������������ɱ�������޵ظ�����");
    this_object()->kill_ob(killer);
    return("��������");
}  
void attempt_apprentice(object ob, object me)
{
  if ( (string)ob->query("family/family_name")=="���޵ظ�") {
    if (((int)ob->query("combat_exp") < 350000 )) {
      command("say " + RANK_D->query_rude(ob) + "�������è�İ�ʽҲ�ҵ������ﶪ�����ۣ�");
      return;
    }
    command("grin");
    command("say �ܺã�" + RANK_D->query_respect(ob) +
       "���Ŭ�������ձض��гɡ�\n");
    command("recruit " + ob->query("id") );
    return;
  }
  command("shake");
  command("say " + RANK_D->query_respect(ob) +
     "������ȥѧЩ��������ɣ�\n");
  return;
}

string ask_chuxian()
{
  object me=this_player();
  if(me->query("family/family_name")!="���޵ظ�")
     return ("�㲻�Ǳ������ˣ�");
  
  command("smile "+me->query("id"));
  return "/d/obj/mieyao"->query_yao(me);
}
 
string ask_cancel()
{
    object me=this_player();
if((int)me->query_temp("m_mieyao"))
{
      me->add("daoxing",-2000);
      me->delete_temp("m_mieyao");
      me->delete("secmieyao");
      me->delete("secmieyao/type");
      me->delete("secmieyao/location");
      me->delete("secmieyao/place");
      me->delete("secmieyao/name");
      me->delete("secmieyao/id");
     return ("û�õĶ�����");
}
else
{
     return ("���������𣿣�");
}
}

int begin_go()
{
	object me,ob;
   	int dx,dx1,wx,qn;
    me=this_player();
	ob=this_object();
	dx=(me->query("daoxing"))/20;
if (dx>=100000) dx=100000;
	dx1=dx/1000;
	wx=(me->query("combat_exp"))/20;
if (wx>=10000) wx=10000;
	qn=30000;
    if (!me->query("fangcun/panlong_visite"))
	  return 0;
    if (me->query("guanli/hell"))
	  return 0;

		if (me->query("fangcun/panlong_hell")=="done")
	{
        message_vision("\n�ز�����������" + RANK_D->query_respect(me) + "�������̸���̨֮Լ��\n"NOR,me);
        message_vision(HIC"\nֻ���ز��������ŵ�ð����һ������,ɲʱ��㲻���ˣ�\n"NOR,me);
    	ob->move("/d/lingtai/inside1");
		return 1;
	}

    if ((me->query("fangcun/panlong_hell_18")=="done")&&(me->query("fangcun/panlong_hell_longjin")=="done"))
	{
		me->add("fangcun/panlong_visite",1);
		me->set("fangcun/panlong_hell","done");
        me->delete("fangcun/panlong_hell_18");
        me->delete("fangcun/panlong_hell_longjin");
    message("chat",HIC+"��"+HIW+"��������"+HIC+"���ز�������(Dizang pusa)��"+me->query("name")+ RANK_D->query_respect(me) +"��������ڤ�ظ�ʮ�˲������Ѱ��������������η��\n"NOR,users());
                 message("chat",HIC+"��"+HIW+"��������"+HIC+"���ز�������(Dizang pusa)��"+me->query("name")+"�õ�����������"+chinese_number(dx1)+"�꣬��ѧ"+wx+"�㣬Ǳ��30000�㣮\n"NOR,users());
   	    if (me->query("family/family_name")=="����ɽ���Ƕ�")
    		message_vision("\n\n�ز��������������ջ���" + RANK_D->query_respect(me) + "ǰ��֪ͨ����һ��.\n"NOR,me);
		me->add("daoxing",dx);
		me->add("combat_exp",wx);
		me->add("potential",30000);
	    if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
			me->set("guanli/hell",1);
		return 1;
	}

			if ((me->query("fangcun/panlong_hell_18")=="done")&&(me->query("fangcun/panlong_hell_longjin")=="begin"))
	{
    		  command("say " + RANK_D->query_respect(me) + "����Ѱ���������\n");
			  return 1;
	}
	        if (me->query("fangcun/panlong_hell_18")=="done")
	        {
        		  command("say " + RANK_D->query_respect(me) + "���书��ֻ�����Щ��������������Խ��Խ�����֣�����" + RANK_D->query_respect(me) + "����Ϊ����
                Ѱ��"+HIY"����"+NOR""+CYN"���������Ƴɸ�����������������ȥ��̨��\n");
				  me->set("fangcun/panlong_hell_longjin","begin");
				  me->set("fangcun/panlong_nowayhell",1);
                  return 1;
			}

			if ((me->query("fangcun/panlong_hell_18")!="begin")&&(me->query("fangcun/panlong_visite")))
    {
  command("say ���Խ���������η����֪" + RANK_D->query_respect(me) + "�㵽���к����ͣ����ܴ�����ڤ��ʮ�˲�����������㲻�٣�\n");
   me->set("fangcun/panlong_hell_18","begin");
	return 1;
	}
  command("say ��ô��" + RANK_D->query_respect(me) + "δ�ܴ�����ʮ�˲������\n");
  command("sigh ");

  return 1;
}

int accept_object(object me, object ob)
{
   if ((me->query("fangcun/panlong_hell_18")=="done")&&(me->query("fangcun/panlong_hell_longjin")=="begin"))
	{	 
	 if (ob->query("id") == "ruan longjin")
	{
	 command ("nod "+me->query("id"));
     command ("say �ã��ã�����Ҫ���������������"+me->query("name")+ RANK_D->query_respect(me) +"�ˣ�\n\n");
     me->set("fangcun/panlong_hell_longjin","done");
	 if (ob->query_temp("iambaddragon"))
     	 me->delete("fangcun/panlong_nowayhell");
      call_out("destroy", 1, ob);
      return 1;
	}
	}
return 0;
}

void destroy(object ob)
{
  destruct(ob);
}

void unconcious()
{
	die();
}

void die()
{
	int i;
	object *inv;
	object who = query_temp("last_damage_from");
	if( objectp(who) && who->query_temp("jingtian/dizang") )
	{
		who->delete_temp("jingtian");
		if( random(who->query("int")) > 10 )
		{
			who->add("jingtian_known",1);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�� �ز�������(Dizang pusa)��" + who->name() + "����ĪҪ���񣬵�����ۡ�����ĳͷ��ɣ�\n\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��" + who->name() + "ɱ���زأ������˵ظ��ǳ�֮��ѧ����"+HIB"[������ʽ����"HIB"��˼"HIR"��ɱ"HIC"ʽ"HIB"]"+HIC"��\n\n\n"NOR,users());
		}
		else
		{
			who->set("jingtian_cant",1);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�� �ز�������(Dizang pusa)��" + who->name() + "����ĪҪ���񣬵�����ۡ�����ĳͷ��ɣ�\n\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��" + who->name() + "ɱ���زأ���ϧ���������ظ��ǳ�֮���޷�����"+HIB"[������ʽ]"+HIC"��\n\n\n"NOR,users());
		}
		
	}
        if( environment() ) 
        {
	        message("sound", "\n�ز��������ƣ��ǲ�����������ȥ�ˡ�����\n\n", environment());
	}
	destruct(this_object());
}
