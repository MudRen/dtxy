//Cracked by Roath
// wenshu-pusa

// #include <ansi.h>

inherit NPC;
inherit F_MASTER;
void create()
{

  set_name("��������", ({ "puxian pusa", "pusa", "pu sa", "puxian" }) );
  set("gender", "����" );
  set("long", @LONG

    ���ͣ�Ϊ��̴������֮һ����������ͬΪ���ȷ��в�̡���˵
���������ڻ��Ϸ����Ϸ���ʮ����Ը�����������Ϊ��ʮ��Ը������
������Ը�������˷�̵�������̸�����ǣ��պ�����Ϊʲ���������
����Ի��������֮ѧ����У���֮������Ī���󣬹ʺ��󡣡�
���󣬼���ζ����Ը�й�󣬹���Բ����
    
LONG );
  set("age",55);
  set("title", "��̴������");
  set("attitude", "peaceful");
  set("rank_info/self", "ƶɮ");
  set("class", "bonze");
  set("max_kee", 5000);
  set("max_gin", 5000);
  set("max_sen", 5000);
  set("force", 4000);
create_family("�Ϻ�����ɽ", 1, "����");
  set("max_force", 2000);
  set("force_factor", 145);
  set("max_mana", 7000);
  set("mana", 60000);
  set("mana_factor", 500);
  set("combat_exp", 5000000);
  set("daoxing", 10000000);

  set_skill("literate", 200);
  set_skill("spells", 200);
  set_skill("buddhism", 200);
  set_skill("unarmed", 200);
  set_skill("jienan-zhi", 200);
  set_skill("dodge", 200);
  set_skill("lotusmove", 200);
  set_skill("parry", 200);
  set_skill("force", 200);
  set_skill("lotusforce", 200);
  set_skill("staff", 200);
  set_skill("lunhui-zhang", 200);
  map_skill("spells", "buddhism");
  map_skill("unarmed", "jienan-zhi");
  map_skill("dodge", "lotusmove");
  map_skill("force", "lotusforce");
  map_skill("parry", "lunhui-zhang");
  map_skill("staff", "lunhui-zhang");
  set("chat_chance_combat", 80);
  set("chat_msg_combat", ({
          (: cast_spell, "bighammer" :),
    }) );

  setup();
  carry_object("/d/obj/cloth/hufa-jiasha")->wear();
}
	
int attempt_apprentice(object ob)
{
	if (!((string)ob->query("bonze/class") =="bonze" )) {
command("say �ҷ�����ͨ���" + RANK_D->query_respect(ob) + "�����������������š�\n");
write("��������������δ��ȳ�����Ϊ���졣\n");
return 0;
}
if (((int)ob->query_skill("buddhism", 1) < 120 )) {
command("say " + RANK_D->query_respect(ob) + "���ڷ��Ͽ��ޣ������ѳ�������\n");
return 0;
}
command("pat " + ob->query("id") );
command("recruit " + ob->query("id") );
return 1;	
}






