//tomcat
//lishanmu.c 2001 by lestat
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_mieyao();
string ask_cancel();
string avenge();
void create()
{
       set_name(HIY"����ʥĸ"NOR, ({"jinling shengmu", "jinling", "shengmu"}));
       set("long", "������ͨ��������µ�������������ʥĸ������������ϼ���ӽ̽�ͽ�ܡ�\n");
       set("title", HIB"������ĸ����"NOR);
       set("gender", "Ů��");
       set("age", 20);
       set("class","yaomo");
       set("attitude", "friendly");
//       set("rank_info/respect", "�ɹ�");
       set("cor", 30);
       set("per", 40);
       set("max_kee", 6500);
       set("max_gin", 800);
       set("max_sen", 6500);
       set("force", 15000);
       set("max_force", 8000);
       set("force_factor", 300);
       set("max_mana", 6500);
       set("mana", 12000);
       set("mana_factor", 250);
       set("combat_exp", 5000000);
	   set("daoxing", 5000000);
       set_skill("literate", 210);
       set_skill("unarmed", 210);
       set_skill("dodge", 210);
       set_skill("force", 210);
       set_skill("parry", 210);
       set_skill("sword", 210);
       set_skill("spells", 210);
       set_skill("whip", 210);
   set_skill("pansi-dafa", 210);
   set_skill("lanhua-shou", 210);
   set_skill("jiuyin-xinjing", 210);
   set_skill("chixin-jian", 210);
   set_skill("qin", 210);
   set_skill("yueying-wubu", 210);
   set_skill("yinsuo-jinling", 210);
   map_skill("spells", "yaofa");
   map_skill("unarmed", "lanhua-shou");
   map_skill("force", "jiuyin-xinjing");
   map_skill("sword", "chixin-jian");
   map_skill("parry", "yinsuo-jinling");
   map_skill("dodge", "yueying-wubu");
   map_skill("whip", "yinsuo-jinling");
   set("inquiry", ([
          "����" : (: avenge :),
          "����": (: ask_mieyao :),
          "cancel": (: ask_cancel :),
]));
   set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: cast_spell, "wuzhishan" :),
                (: cast_spell, "ziqi" :),
                (: perform_action, "whip.tian" :),
                (: perform_action, "whip.wang" :),            
}) );
create_family("��˿��", 1, "��");
setup();

        carry_object("/d/obj/cloth/tianyi.c")->wear();
        carry_object("/d/obj/weapon/whip/longsuo")->wield();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void attempt_apprentice(object ob)
{

   if ( (string)ob->query("family/family_name")=="��˿��") {
        if (((int)ob->query("combat_exp") < 1000000 )) {
        command("say " + RANK_D->query_respect(ob) +"�ĵ��в��������Щ��ѧ�ط�������������\n");
        return;}
/*if ( !((string)ob->query("gender")=="Ů��")){
        command("shake");
        command("say ������˿��ֻ��Ůͽ����λ" +RANK_D->query_respect(ob) + "��������߾Ͱɡ�\n");
        return;}*/
        command("pat "+ob->query("id"));
        command("say �ã�ϣ��" + RANK_D->query_respect(ob) +"������ϼ�������ϣ��Ҿ��������ˡ�\n");
        command("recruit " + ob->query("id") );
        return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +"�Ҳ���ʶ��ɡ�\n");
        return;
}

int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
    ob->set("class", "yaomo");
    ob->set("title", HIC"������ĸ����"NOR);
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
    tell_room(where,"ֻ������ʥĸ�����һָ��\n");
    tell_room(where,"����������ڣ���ȥ��"+killer->query("name")+"ץ����\n");
    tell_room(environment(killer),"�������һֻ���ֽ�"+killer->query("name")+"ץ���ˡ�\n");
    killer->move(where);
    tell_room(where,killer->query("name")+"���ӿ�������������\n");
    command("say ���ϣ�����ɱ������˿������");
    this_object()->kill_ob(killer);
    return("��������");
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