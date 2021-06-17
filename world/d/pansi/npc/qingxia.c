
//zixiaxianzi.c 2001 by lestat
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_mieyao();
string ask_cancel();
string avenge();
string give_zui(object me);
void create()
{
       set_name(MAG"��ϼ����"NOR, ({"qingxia xianzi", "qingxia", "xianzi","master"}));
       set("long", "������ϼ���ӵ��������,���������������ϼ��������һ�õ�о�������ϼ����˼��
�½翪ɽ����,��׷���˴���\n");
       set("title", HIY"�����о"NOR);
       set("gender", "Ů��");
       set("age", 20);
       set("class","yaomo");
       set("attitude", "friendly");
       set("rank_info/respect", "С����");
       set("cor", 30);
       set("per", 21);
       set("max_kee", 4500);
       set("max_gin", 800);
       set("max_sen", 4500);
       set("force", 4000);
       set("max_force", 2400);
       set("force_factor", 125);
       set("max_mana", 1800);
       set("mana", 3000);
       set("mana_factor", 150);
       set("combat_exp", 1600000);
	   set("daoxing", 3000000);
       set_skill("literate", 150);
       set_skill("unarmed", 180);
       set_skill("dodge", 160);
       set_skill("force", 160);
       set_skill("parry", 150);
       set_skill("sword", 180);
       set_skill("spells", 150);
       set_skill("whip", 180);
   set_skill("pansi-dafa", 160);
   set_skill("lanhua-shou", 160);
   set_skill("jiuyin-xinjing", 150);
   set_skill("qingxia-jian", 200);
   set_skill("yueying-wubu", 150);
   set_skill("yinsuo-jinling", 150);
   map_skill("spells", "pansi-dafa");
   map_skill("unarmed", "lanhua-shou");
   map_skill("force", "jiuyin-xinjing");
   map_skill("sword", "qingxia-jian");
   map_skill("parry", "yinsuo-jinling");
   map_skill("dodge", "yueying-wubu");
   map_skill("whip", "yinsuo-jinling");
   set("chat_chance_combat", 50);
   set("inquiry", ([
//          "����" : (: avenge :),
          "��ϼ" : "�Ҿ��������Ǹ��������˵�.",
    	  "��ϼ����" : "�Ҿ��������Ǹ��������˵�.",
//		  "��������" : (: give_zui :),
 //          "����": (: ask_mieyao :),
 //          "cancel": (: ask_cancel :),
]));
   set("no_zui", 0);
create_family("��˿��", 1, "��");
setup();

        carry_object("/d/obj/cloth/tianyi.c")->wear();
        carry_object("/d/obj/weapon/sword/qinghong")->wield();
        carry_object("/d/ourhome/obj/shoes")->wear();
}
void init()
{
add_action("do_kneel","kneel");
add_action("do_yes", "yes");
}
string avenge()
{
    object who=this_player(),killer,where;
    string killid;
    if((string)who->query("family/family_name")!="��˿��")
        return ("�㲻�Ǳ��ɵ��ӣ��������Һθɣ�");
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
    tell_room(where,"ֻ����ϼ���������һָ��\n");
    tell_room(where,"����������ڣ���ȥ��"+killer->query("name")+"ץ����\n");
    tell_room(environment(killer),"�������һֻ���ֽ�"+killer->query("name")+"ץ���ˡ�\n");
    killer->move(where);
    tell_room(where,killer->query("name")+"���ӿ�������������\n");
    command("say ���ϣ�����ɱ������˿������");
    this_object()->kill_ob(killer);
    return("��������");
} 
void attempt_apprentice(object ob)
{
   /*if ( !((string)ob->query("gender")=="Ů��")){
      command("shake");
          command("say ������˿��ֻ��Ůͽ����λ" + RANK_D->query_respect(ob) + "��������߾Ͱɡ�\n");
      return;
   }*/

   if ( (string)ob->query("family/family_name")=="��˿��") {
   if (((int)ob->query("daoxing") < 500000 )) {
   command("say " + RANK_D->query_respect(ob) +
"�ĵ��в��������Щ��ѧ�ط�������������\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("say �ã�ϣ��" + RANK_D->query_respect(ob) +
"���Ŭ������������˿��������\n");
       command("recruit " + ob->query("id") );
	   ob->set("title", "��˿����ϼ���Ӵ���");
           ob->set("class", "yaomo");
   return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"������ȥѧЩ��������ɡ�\n");
        return;
}
int accept_fight(object me)
{
   return 0;
}

string ask_mieyao()
{
    object who=this_player();

    if((string)who->query("family/family_name")=="��˿��") {
      command("smile "+who->query("id"));
      return "/d/obj/mieyao"->query_yao(who);
    }
    return ("��������,�ι�����?\n");
}
int do_kneel()
{
    object who = this_player();
    if((string)who->query("family/family_name")!="��˿��")
     return notify_fail(this_object()->query("name")+"˵�����ֲ��������µ��ӣ����Ҹ�ʲô��\n");
   if("/d/obj/mieyao"->delete_mieyao(who)){
        command("say ��Ȼ��ˣ������˰ɣ�������û��������񣬵���Щ�ͷ���\n");
	who->add("faith",-5);
        message_vision("$N���ҳ϶��½��ˣ�\n",who);
     }
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

void destroy(object ob)
{
        destruct(ob);
        return;
}

void dropthing(string thing)
{
  command("drop "+thing);
  return;
}
int accept_object(object me,object ob)
{       
	    string myname=RANK_D->query_respect(me), thing=(string)ob->query("id");
		object who;
        who=this_object();
  if (me->query("fangcun/panlong_pansi")=="begin")
	{
	  if ((ob->query("id") == "yinsuo jinling")&&(ob->query_temp("zixia_xianzi")))
      {
      command ("sigh");
//	  me->set_temp("qingxia_xianzi","give");
      message_vision(MAG"\n\n��ϼ����"+HIY"����˵Щʲô��ͻȻ��������ɲ�Ǽ��ɳ��ʯ���������������۾���\n"NOR,me);
      call_out("destroy", 1, ob);
	  call_out("tianbing_come",3,me,who);
      return 1;
	  }
	  command ("say ����ʲô��");
      call_out("dropthing", 1, thing);
      return 1;
    }
  command ("shake ");
  return 0;
}

void tianbing_come(object me,object ob)
{
   object erlang,dog;
   erlang=new("/d/pansi/npc/erlangshen");
   dog=new("/d/pansi/npc/dog");
   message_vision(NOR"\n\nֻ��"+HIY"������"+NOR"�ֳ���������ǹ������"+HIY"Х��Ȯ"+NOR"ɱ�����ڵĳ�"+MAG"��ϼ����"+NOR"������\n"NOR,me);
   me->set("fangcun/panlong_nowaypansi",1);
   me->set_temp("give_suo",1);
   me->delete("fangcun/panlong_pansi");
   erlang->move(environment(me));
   erlang->set_temp("killer_me",1);
   erlang->set("killer","zixia xianzi");
   dog->move(environment(me));
   dog->set_temp("killer_me",1);
   message_vision(HIY"\n\n$N������������ǹһ������ȵ�����ϼ�������������ϼ˽���½磬���������������Ҿ�������
   ������������������������         �����������ʾ�����������ɣ�\n"NOR, erlang);
   call_out("zixia_out",3,me);
}

void zixia_out(object me)
{
	object zixia;
	zixia=new("/d/pansi/npc/zixia");
	zixia->move(environment(me));
      message_vision("\n\n�����������֮�ʣ�ͻȻ���ٲ���Ʈ����һ����Ӱ��$N����һ��ԭ������ϼ���ӣ�\n"NOR,me);
      message_vision(MAG"\n\n\n��ϼ��Цһ�������ߣ�������ʲô��������\n"NOR,me);
      message_vision(HIM"\n\n\n��ϼ���ӵ����������ߣ���ǧ���ˣ��Ҳ����ٶ��ˣ��ң��������Ҿ�����ôһ����㣮\n"NOR,me);
      message_vision(MAG"\n\n��ϼ���ӣ�������������\n\n"NOR,me);
	  call_out("fight_erlang",5,me);
}

void fight_erlang(object me)
{
     
	message_vision("\n\n\n"+HIM"��ϼ����"+NOR"�������ϵ���������"+MAG"��ϼ����"+NOR"һ��������罣��һͬ������ꯣ�\n"NOR,me);
     message_vision(HIY"\n\n\n��꯹�����Ц�����������ã�����һ�������ˣ�\n"NOR,me);
     message_vision(HIY"\n\n\n��꯶���$N�����ҷ����ּ��ǰ�����ˣ����ȵ��ҿ�ּ�����ߣ���ɱ���ۣ�\n\n\n"NOR,me);
    call_out("fightings",2,me);
}

void fightings(object me)
{
	object erlang,dog,zixia,qingxia;
	 erlang=present("erlang zhenjun",environment(me));
	 dog=present("xiaotian quan",environment(me));
	 qingxia=present("qingxia xianzi",environment(me));
	 zixia=present("zixia xianzi",environment(me));
	     erlang->kill_ob(qingxia);
	 erlang->kill_ob(zixia);
	 dog->kill_ob(qingxia);
	 dog->kill_ob(zixia);
}


void die()
{
	object zixia,erlang;
	object me=this_object();
    zixia=present("zixia xianzi");
	erlang=present("erlang zhenjun");
   if (!erlang)
	   return ::die();
   if (!zixia)
	{
	   message_vision(HIY"\n\n\n��꯴Ӷ��ϵ���ֻ�������һ����⣬"+MAG"��ϼ"+HIY"����֮�¶�ܲ��������ԭ�Σ�����һ����о������꯵����У�\n"NOR,me);
	  message_vision(HIY"\n\n\n�����������Ц��������������оҲ�Ҹ���"+HIR"�ѻ�������"+HIY"���֣����ǲ���������\n"NOR,me);
	  message_vision("\n\n\n�Աϼ�һ�����Ц��ȥ��\n"NOR,me);
      destruct(erlang);
	  if (present("xiaotian quan"))
        {    
            message("sound", "\n\nХ��ȮҲ�����Ŷ������ﳤ��ȥ��\n\n", environment());
            destruct(present("xiaotian quan"));
        }
      destruct(me);
	  return;
	}
	   message_vision(HIY"\n\n\n��꯴Ӷ��ϵ���ֻ�������һ����⣬"+MAG"��ϼ"+HIY"����֮�¶�ܲ��������ԭ�Σ�����һ����о������꯵����У�\n\n\n"NOR,me);
      destruct(me);
}
