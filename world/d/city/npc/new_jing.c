inherit NPC;
#include <ansi.h>
  int give_bonnet();
    int give_dan();
int answer_me();
   int accept_object(object who, object ob)
{
                    if( (string)ob->query("id")=="loyal bonnet" )
{
who->set("yudian/bonnet",0);
                    command("say �ý�û����ٽ費�ѡ�");
    return 1;
}
}
void create()
{
         set_name(HIY"���"NOR, ({"guan jia","guanjia"}));
   set ("long", @LONG
    ���������︺�����ҷ�����(gift)Ŷ��
    �����ϻ�����ʦ����(bonnet)��!
    �������ȥ����(ask)�����ǵã���ʦ����������Ҫ��Ŷ��
LONG);
           set("gender", "Ů��");
              set("title",HIG"�����ܼ�"NOR);
                 set("age", 20);
        set("per", 40);
       set("attitude", "peaceful");
       set("shen_type", 1);
//  carry_object("/u/yudian/weapon/mmjian")->wield();
//  carry_object("/u/yudian/hak")->wear();
set("inquiry", ([
           "bonnet":(:give_bonnet:),
          "gift":(:give_dan:),
            "����":(:give_dan:),
            "��ʦ����":(:give_bonnet:),
            "����":(:give_bonnet:),
           "name":(:answer_me:),
]));
        setup();
}
void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
}
}
int answer_me()
{
command("say ���ǳ����ܼ���㣬������
������ʦ���ں����������ҵġ�\n");
return 1;
}
int give_dan()
{
object dan;
object who=this_player();
if (!userp(who))
{
command("heng");
command("say ʲôСèС��Ҳ��Ҫ�����");
command("qi");
return 1;
}
         if (this_player()->query("yudian/gift")=="got")
{
          message_vision("$N����$n����һ����\n",this_object(),this_player());
       command("say ����ֻ��һ�ݣ�����Ͳ����ˣ�");
  return 1;
}
//    dan=new("/u/yudian/obj/new_dan");
//    dan->move(who);
//message_vision("$N����������������!\n$N��$nһ�����ɾ�����ң����\n",this_object(),this_player());
who->set("combat_exp",20000);
who->set("daoxing",20000);
who->set("force",400);
who->set("max_force",400);
who->set("max_mana",400);
who->set("mana",400);
who->set("maximum_force",400);
who->set("maximum_mana",400);
who->set("potential",20000);
message_vision("$N����������������!\n$N��һָ��$nֻ����������Ѫ���ڣ��ƺ���ѧ�����ж�����������\n",this_object(),this_player());
     who->set("yudian/gift","got");
return 1;
}
 int give_bonnet()
 {
 object bonnet;
 object who=this_player();
if (!userp(who))
{ 
command("heng");
command("say ʲôСèС��Ҳ��Ҫ��������");
command("qi");
return 1;
}
          if (this_player()->query("yudian/bonnet")=="got")
 {
           message_vision("$N����$n����һ����\n",this_object(),this_player());
          command("say �ϴθ���Ļ�û���أ������ˣ�");
   return 1;
  }
      bonnet=new("/d/lingtai/obj/faguan");
  bonnet->move(who);
message_vision("$N����������������!ֻ������ѩ�ɣ�$N���һ����ʦ���ڡ�\n$N��$nһ����ʦ���ڡ�\n",this_object(),this_player());
      who->set("yudian/bonnet","got");
           command("say �����˼ǵû���Ŷ�������´β����ˣ�");
 return 1;
  }
void greeting(object ob)
{
         if( !ob || !visible(ob) || environment(ob) != environment() || ob->query("yudian/gift")=="got") return;
say(name()+"���ص�˵������Ҫ���������Ұ�����������ֻ��һ�λ���Ŷ����������\n"NOR);

/*
if (random(10))
{
  switch(random(19))
  {
   case 0:
	message("system", HIM"������������ŨŨ�Ľ�������,���ھ�Ҫ����!\n"NOR,users());
	break;
   case 1:
	message("system", HIR"���һ����غ��ڿ���Ѥ�õ�����...\n"NOR,users());
	break;
   case 2:
	message("system", HIG"������Եȫ����ʦף���´����!\n"NOR,users());
	break;
   case 3:
	message("system", HIM"������Եȫ����ʦף���µ�һ����������!!\n"NOR,users());
	break;
   case 4:
	message("system", HIY"������Եȫ����ʦף���µ�һ�깤��˳��!\n"NOR,users());
	break;
   case 5:
	message("system", HIY"������Եȫ����ʦף�������һ��ѧϰ����!\n"NOR,users());
	break;
   case 6:
	message("system", HIG"������Եȫ����ʦף�������һ�����彡��!\n"NOR,users());
	break;
   default:
	break;
  }
}
*/
}
