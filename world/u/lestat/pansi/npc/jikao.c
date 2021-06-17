//jikao.c��˿�����ؿ���������
//2001 by lestat
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int give_qin(object ob);
void create()
{
       set_name("���ؿ�", ({"ji yikao", "ji","yikao"}));
       set("long",
"���������£����˿��ţ�һ����ף�����鶯�ˡ�������֮��,�ó�����,Ϊ
�����������볯������л��,Ϊ槼�����,����ƽ�����º󱻷�Ϊ�嶷��������
�챱����΢���,��������˿����,���������︧�١�\n");
       set("title", MAG"���챱����΢���"NOR);
       set("gender", "����");
       set("age", 20);
       set("class", "yaomo");
       set("attitude", "friendly");
       set("rank_info/respect", "����");
       set("per", 100);
       set("int", 40);
       set("max_kee", 10000);
//       set("max_gin", 2600);
       set("max_sen", 10000);
       set("force", 12000);
       set("max_force", 5800);
       set("force_factor", 500);
       set("max_mana", 8000);
       set("mana", 10000);
       set("mana_factor", 400);
       set("combat_exp", 5000000);
       set("daoxing", 6000000);
       set("eff_dx", 800000);
       set("nkgain", 350);
       set_skill("literate", 600);
       set_skill("unarmed", 260);
       set_skill("dodge", 300);
       set_skill("force", 280);
       set_skill("parry", 290);
       set_skill("sword", 300);
       set_skill("spells", 250);
       set_skill("whip", 300);
       set_skill("qin", 600);
       set_skill("pansi-dafa", 280);
       set_skill("lanhua-shou", 240);
       set_skill("jiuyin-xinjing", 270);
       set_skill("qingxia-jian", 270);
       set_skill("yueying-wubu", 280);
       set_skill("yinsuo-jinling", 300);
       set_skill("chixin-jian", 300);
       map_skill("spells", "pansi-dafa");
       map_skill("unarmed", "lanhua-shou");
       map_skill("force", "jiuyin-xinjing");
       map_skill("sword", "chixin-jian");
       map_skill("parry", "chixin-jian");
       map_skill("dodge", "yueying-wubu");
       map_skill("whip", "yinsuo-jinling");
set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: cast_spell, "ziqi" :),
                (: perform_action, "sword.haotan" :),      
}) );
       set("inquiry", ([
                "����" : "�����������Σ��������������ٹ��ޣ��������������ַ�Ŀ��������
                ���������а˷�����Ĩ�����������ޣ�Ʋ���У��У��������ɣ����߲�����",
		"��" : "������̫���������ֶ����ţ������ִ���ͬ�������а�ʮһ�������
		ʮһС������ʮ��������",
		"�˷�" : "�˷�����Ĩ�����������ޣ�Ʋ���У��У���",
		"����" : "�Ű�����ר���£���ŭ�黳��������",
		"�߲���" : "�������꣬�󱯴󰧣��¹ڲ����������Կ������������֪����
		�ף�������ࣻ���˽Բ�����",
                "����" : "���̽�����",
                "������" : (: give_qin :),
                "qin" : (: give_qin :),
		]) );
   set("chat_chance",1);
   set("chat_msg", ({
   	CYN"����ƽ������Ŀ����������������������ǧ��ʥ���ģ�����������ͩľ��\n"NOR,
/*        CYN"�ؿ���ϥ���ڵ��ϣ����ٷ���ϥ�ϣ�ʮ���Ⲧ�����ң���Ūһ������Ի��"HIG"������"NOR+CYN"��
             ����������Ū��磬�һ�����ӳ�պ죻���������̽��壬�����������������
�������������������������Σ��������������˳����ˬ�������������ط��ڣ�\n"NOR,*/
        }));


create_family("��˿��", 1, "����");
setup();

  carry_object("/d/npc/obj/qin")->wield();//װ����ħ��
//  carry_object("/obj/loginload/mancloth1")->wear();
//  carry_object("/obj/loginload/linen")->wear();
  carry_object("/d/pansi/obj/qin");//Я��������
  carry_object("/d/npc/obj/armor")->wear();
  carry_object("/d/npc/obj/pifeng")->wear();
}

void attempt_apprentice(object ob)
{
   if ( (string)ob->query("family/family_name")=="��˿��") {
   	 if (ob->query("obstacle/number") < 26) {
        command("say ��λ" + RANK_D->query_respect(ob) + "�㻹���ȳ�ȥ����һ���ɣ�\n");
        command("sigh");
        return;
        }
        if (((int)ob->query("daoxing") < 1000000 )) {
        command("say " + RANK_D->query_respect(ob) +"�ĵ��в��������Щ��ѧ�ط�������������\n");
        return;
}
/*if ( !((string)ob->query("gender")=="Ů��")){
           command("shake");
           command("say ��˿��ֻ��Ůͽ����λ" +
RANK_D->query_respect(ob) + "��������߾Ͱɡ�\n");
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
    ob->set("title", MAG"��ָ��ħ"NOR);
}

int give_qin(object ob)
{
   object who, me;
   who=this_player();
   me=this_object();

   if( (string)who->query("family/family_name")!="��˿��" ) {
     if( (int)who->query_temp("pending/ask_time") >= 3) {
        message_vision("$NͻȻ���𣬶�ݺݵĵ���$n˵���������ǲ�����ˣ�\n", me, who);
        command("kill " + who->query("id"));
        return 1;
        }
     message_vision("$Nбб�����$nһ�ۣ�˵���˲���Ϊ���˵�Ҳ��\n", me, who);
     who->add_temp("pending/ask_time", 1);
     return 1;
   }
   if( (int)me->query("have") ){
     
     command("give qin to " + who->query("id"));
     me->delete("have");
     return 1;
   }
   message_vision("$N��$n���ε�һ���֣�˵�����ѷ����ˣ�������������ɡ�\n", me, who);
   return 1;
}
void die()
{
        if( environment() ) {
message("sound", "\n\n���ؿ�ŭ��,������������������\n\n", environment());
message("sound", "\n˵��һ������,����һ�����������ȥ������\n\n", environment());
        }
        destruct(this_object());
}
