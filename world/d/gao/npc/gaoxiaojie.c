// gao.c

inherit NPC;
int leave_here();

void create()
{
       set_name("��С��", ({"gao xiaojie", "xiaojie", "gao"}));
       set("long","��ׯ����Ů�����������ˣ�\n");
       set("gender", "Ů��");
       set("age", 40);
       set("attitude", "peaceful");
       set("shen_type", 1);
	set("per", 30);
	set("combat_exp", 7400);
        set_skill("unarmed", 10);
	set_skill("dodge", 50);
	set_skill("parry", 20);
	setup();
//       add_money("gold", 1);
        carry_object("/d/gao/obj/pink_cloth")->wear();

set("inquiry", ([
"�뿪" : (: leave_here :),
"leave" : (: leave_here :),
]) );

}

int leave_here()
{
 object me=this_player();
 object ob=this_object();
 object obp;
 if (me->query_temp("obstacle/yuanwai")==1)
 {
 	say("�Ǿ����ʹ����ˣ�\n");
 	say("��С��ת���С�ų�ȥ�ˣ�\n");
 	me->set_temp("obstacle/gao_asked",1);
	destruct(ob);
 }
 else
 {
 	say("����Ȼ��֪������˵ʲô��\n");
 }
 return 1;
}
