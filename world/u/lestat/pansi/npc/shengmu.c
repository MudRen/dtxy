//tomcat
//lishanmu.c 2001 by lestat
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
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
   set_skill("yaofa", 210);
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

