inherit NPC;

void create()
{
        set_name("�׺�ͯ��", ({"baihe tongzi", "tongzi"}));
        set("gender", "����" );
        set("age", 14);
        set("long", "Ԫʼ�����������ͯ��\n");
        set("combat_exp", 1000);
        set("attitude", "peaceful");
        set_skill("dodge", 20);
   set("class", "shen");
        set_skill("parry", 70);
        set_skill("unarmed", 60);  
        set("per", 40);
        set("max_kee", 800);
        set("max_sen", 800);
        set("force", 700);
        set("max_force", 700);
        set("force_factor", 15);
   set("max_mana", 800);
   set("mana", 800);
   set("mana_factor", 1);
        setup();
   carry_object("/d/obj/cloth/linen")->wear();
}
