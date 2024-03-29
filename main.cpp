#include <iostream>
#include <queue>
using namespace std;

/*
 * Meetings management
 *      Luz Clara Mora Salazar
 *      Bryam Lopez Miranda
 *      Estefania Perez Hidalgo
 */

//------ Prototype section -----

void HardCode();
bool addAdmin(string, int, string);
struct Administrators*searchAdmin(string, int);
struct Teachers*searchTeacher(string, int);
bool addTeacher(string, int, string);
struct Students*searchStudent(string, int);
bool addStudent(string, int, string);
struct Courses*searchCourse(string);
bool addCourse(string, string, int);
void updateTeachersList();
void updateStudentsList();
void print(string);
struct Students;
struct Courses;
struct Administrators;
struct LinkTeacher;
struct LinkStudent;
struct Meeting;
struct SublistAssistance;
bool searchDate(Meeting*meet);

int hr=0;
char c;
int mins=0;
char d;
int dy = 0;
int mth = 0;
int yr = 0;
char a;
char b;

//------ End of the prototype section -----

struct Teachers{
    string fullName;
    int id;
    string gender;
    Teachers*next;
    Teachers*previous;
    LinkTeacher*link;

    Teachers(string fn, int i, string g){
        fullName=fn;
        id=i;
        gender=g;
        next=NULL;
        previous=NULL;
        link=NULL;
    }

}*firstTeacher;

struct Students{
    string fullName;
    int id;
    string gender;
    Students*next;
    LinkStudent*link;

    Students(string fn, int i, string g){
        fullName=fn;
        id=i;
        gender=g;
        next=NULL;
        link=NULL;
    }

}*firstStudent;

struct Courses{
    string name;
    string code;
    int credits;
    Courses*next;

    Courses(string n, string c, int cred) {

        name=n;
        code=c;
        credits=cred;
        next=NULL;
    }
}*firstCourse;

struct Administrators{

    string fullName;
    int id;
    string gender;

    Administrators*next;
    Teachers*subListT;
    Students*subListS;
    Courses*subListC;

    Administrators(string fn, int i, string g){

        fullName=fn;
        id=i;
        gender=g;
        next=NULL;
        subListT=firstTeacher;
        subListS=firstStudent;  //la sublista es igual a la lista general ya que es compartida
        subListC=firstCourse;

    }
}*firstAdmin;

struct LinkTeacher{
    //Esta es una lista de enlace de profesor a un curso, tambíen contiene una sublista de enlaces de reuniones
    //del tipo Meeting para llevar lista de reuniones que un profesor tiene en el curso al que apunta el enlace

    LinkTeacher*next;
    Courses*course;
    int group;
    Meeting*firstMeeting;

    LinkTeacher(int g){
        next=NULL;
        course=NULL;
        group=g;
        firstMeeting=NULL;
    }

};
struct LinkStudent{
    //Esta es una lista de enlace de estudiante a un curso, tambíen contiene una sublista de enlaces de asistencia del
    //tipo SubListAssistance para llevar lista de asistencia que un estudiante tiene en el curso al que apunta el enlace

    LinkStudent*next;
    Courses*course;
    int group;
    SublistAssistance*sublistAssistance;

    LinkStudent(int g){
        next=NULL;
        course=NULL;
        group=g;
        sublistAssistance=NULL;
    }

};

struct SublistAssistance{
    //Sublista de asistencia perteneciente a cada enlace de la lista del tipo LinkStudent, guarda ID de la reunión si un
    // estudiante participó en una reunión

    int id;
    SublistAssistance*next;

    SublistAssistance(int iD){
        id=iD;
        next=NULL;
    }
};

struct Meeting{
    //Sublista de asistencia perteneciente a cada enlace de la lista del tipo LinkStudent, guarda ID de la reunión si un
    // estudiante participó en una reunión

    Meeting*next;
    int id;
    int hour;
    int minute;
    int hourEnd;
    int minuteEnd;
    int day;
    int month;
    int year;
    string meetingTitle;

    Meeting(int iD, int hourr, int minutee, int hourEndd, int minuteEndd,int dayy, int monthh, int yearr, string title){

        id=iD;
        hour=hourr;
        minute=minutee;
        hourEnd=hourEndd;
        minuteEnd=minuteEndd;
        day=dayy;
        month=monthh;
        year=yearr;
        meetingTitle=title;
        next=NULL;

    }

};

Administrators*searchAdmin(string fullName, int id){
    //busca admin a ver si ya existe, retorna NULL si no está

    Administrators*temp=firstAdmin;

    while(temp != NULL){
        if(temp->fullName==fullName){//Lo busca por nombre
            cout<<"\nThe name is already part of the administrators\n"<<endl;
            return temp;
        }else if(temp->id==id){//Lo busca por ID
            cout<<"\nThe ID is already part of the administrators\n"<<endl;
            return temp;
        }
        temp=temp->next;
    }
    return NULL; //if return NULL the admin is not

}

bool addAdmin(string fullName, int id, string gender){
    //función que agrega administadores a lista simple con inserción al inicio

    if(firstAdmin==NULL){
        //si lista de admins está vacía se agrega nuevo admin
        Administrators*nn = new Administrators(fullName, id, gender);
        firstAdmin=nn;
        return true;
    }else{
        Administrators*admin=searchAdmin(fullName, id);//si retorna  NULL el admin no existe, sino ya existe

        if(admin != NULL){//est esta el admin
            cout<<"Administrator could not be added because it already exists"<<endl;

            return false;
        }else{
            Administrators*nn= new Administrators(fullName, id, gender);//crea al admin

            nn->next=firstAdmin;
            firstAdmin=nn;      //hace inserción al inicio de lista simple

            return true;
        }
    }
}

Teachers*searchTeacher(int id){//busca teacher a ver si ya existe, retorna NULL si no está

    Teachers*temp=firstTeacher;

    while(temp != NULL){
        if(temp->id==id){//Lo busca por ID
            return temp;
        }
        temp=temp->next;
    }
    return NULL; //if return NULL the teacher is not

}

bool addTeacher(string fullName, int id, string gender){
    //función que agrega aprofesor a lista doble con inserción al inicio

    if(firstTeacher==NULL){
        //si lista de profes está vacía se agrega nuevo profe
        Teachers*nn = new Teachers(fullName, id, gender);
        firstTeacher=nn;
        return true;
    }else{
        Teachers*teacher=searchTeacher(id);//si retorna  NULL el teacher no existe, sino ya existe

        if(teacher != NULL){//esta el teacher
            cout<<"Teacher could not be added because it already exists"<<endl;

            return false;
        }else{
            Teachers*nn= new Teachers(fullName, id, gender);//crea al admin

            nn->next=firstTeacher;
            firstTeacher->previous=nn; //inserción al inicio de lista doble
            firstTeacher=nn;

            return true;
        }
    }
}

Students*searchStudent(int id){//busca student a ver si ya existe, retorna NULL si no está

    Students*temp=firstStudent;

    while(temp != NULL){//do while por si hay solo un elemnto en lista
        if(temp->id == id){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;

}

bool addStudent(string fullName, int id, string gender){//función que agrega estudiante a lista circular con inserción ordenada

    if(firstStudent==NULL){//si lista de estudianes está vacía se agrega nuevo estudiante
        Students*nn = new Students(fullName, id, gender);
        firstStudent=nn;
        return true;
    }else{
        Students*student = searchStudent(id);//si retorna  NULL el estudiante no existe, sino ya existe

        if(student != NULL){//esta el estudiante
            cout<<"Student could not be added"<<endl;
            return false;
        }else{
            Students*nn= new Students(fullName, id, gender);//crea al estudiante

            Students*temp=firstStudent;

            while(temp != NULL){//compara el id del nn con el anterios temp y temp->next

                if(nn->id >=temp->id &&  temp->next == NULL){
                    //si nn tiene mayor ID que todos los demás se agrega a lista preguntando si id de nn es mayor al
                    //id de temp y el temp siguiente es NULL osea, nn sería al mayor de id
                    temp->next = nn;
                    return true;
                }
                if(nn->id >=temp->id && nn->id <= temp->next->id){
                    //si id nn es un elemento central osea ni el menor ni el mayor se agrega a su lugar correspondiente

                    nn->next = temp->next;
                    temp->next = nn;
                    return true;
                }

                temp = temp->next;
            }

            if(nn->id <= firstStudent->id){//si es mayor al primero
                //si nn es el id menor se agrega de primero y se convierte en el firstStudent
                nn->next=firstStudent;
                firstStudent=nn;
                return true;
            }

        }
    }
    return false;
}

Courses*searchCourse(string code){
    //busca teacher a ver si ya existe, retorna NULL si no está

    Courses*temp=firstCourse;

    do{
        if(temp->code == code){
            return temp;
        }
        temp=temp->next;
    } while(temp != firstCourse);

    return NULL;
}

bool addCourse(string name, string code, int credits){//función que agrega aprofesor a lista doble con inserción al inicio

    if(firstCourse==NULL){//si lista de profes está vacía se agrega nuevo profe
        Courses*nn = new Courses(name, code, credits);
        firstCourse=nn;
        firstCourse->next=firstCourse; //se hace la lista circular
        return true;
    }else{
        Courses*course=searchCourse(code);//si retorna  NULL el teacher no existe, sino ya existe

        if(course != NULL){//esta el teacher
            cout<<"Course could not be added"<<endl;

            return false;
        }else{
            Courses*nn= new Courses(name, code, credits);//crea al admin

            Courses*temp= firstCourse;

            while(temp->next != firstCourse){
                temp=temp->next;
            }
            temp->next=nn;
            nn->next=firstCourse;
            return true;
        }
    }
}

void updateTeachersList(){//Actializa en firstTeacher en cada admin
    /*
     * Cuando un profesor se agrega al inicio de lista profesores o se agrega por primera vez
     * la lista esta desactualizada por eso existe esta función para actualizar las sublista a
     * los datos existentes actualmente
     * Solo se llama en casos específicos y no siempre que se agregue un profesor
     */
    Administrators*temp=firstAdmin;

    while(temp != NULL){
        temp->subListT=firstTeacher;
        temp=temp->next;
    }
}
void updateStudentsList(){//Actializa en firstStudent en cada admin
    /*
     * Cuando un estudiante se agrega al inicio de lista estudiantes o se agrega por primera vez
     * la lista esta desactualizada por eso existe esta función para actualizar las sublista a
     * los datos exixtentes actualmente
     * Solo se llama en casos específicos y no siempre que se agregue un estudiante
     */
    Administrators*temp=firstAdmin;

    while(temp != NULL){
        temp->subListS=firstStudent;
        temp=temp->next;
    }
}

bool relateTeacherCourse(int idTeacher, string codeCourse, int group){
    Teachers*teacher=searchTeacher(idTeacher);
    if(teacher==NULL){
        cout<<"\nThe teacher is not in the list, the link cannot be made"<<endl;
        return false;
    }
    Courses*course=searchCourse(codeCourse);
    if(course==NULL){
        cout<<"\nThe course is not in the list, the link cannot be made"<<endl;
        return false;
    }

    LinkTeacher*nn=new LinkTeacher(group);
    nn->course=course;

    LinkTeacher*temp=teacher->link;
    if(temp==NULL){
        teacher->link=nn;
        return true;
    }else{
       do{
           /*
            * Este ciclo al mismo tiempo que busca posicionarse en la ultima posición de la lista para agregar el
            * nuevo curso al profesor también comprueba que el curso y grupo no se metan de manera repetida al
            * mismo profesor, por eso es un ciclo do while
            */
            if(temp->course->code == nn->course->code && temp->group == nn->group){
                cout<<"This teacher has already assigned this group and course"<<endl;
                return false;
            }
            if(temp->next==NULL){
                break;
            }
            temp=temp->next;
        } while(temp != NULL);
        temp->next=nn;

        return true;
    }
}

bool relateStudentCourse(int idStudent, string codeCourse, int group){
    Students*student=searchStudent(idStudent);//se busca a estudiante en lista
    if(student==NULL){
        cout<<"\nThe student is not in the list, the link cannot be made"<<endl;
        return false;
    }
    Courses*course=searchCourse(codeCourse);//se busca curso en lista
    if(course==NULL){
        cout<<"\nThe course is not in the list, the link cannot be made"<<endl;
        return false;
    }

    bool courseFoud=false;//variable para comprobar si el curso está siendo impartido

    Teachers*tempT=firstTeacher;
    while(tempT != NULL){
        /*
         * Este ciclo comprueba que el curso esté siendo impartido por un profesor para poder asignarselo a un estudiante
         * si el curso sí está siendo impartido la variable courseFound cambia a true, si no cambia al terminar todo
         * el ciclo while el curso no está siendo impartido, aunque esté en la lista de curso
         */
        LinkTeacher*tempL=tempT->link;
        while(tempL != NULL){
            if(tempL->course == course && tempL->group == group){
                courseFoud=true;
                break;
            }
            tempL=tempL->next;
        }
        if(courseFoud){
            break;
        }
        tempT=tempT->next;

    }
    if(courseFoud==false){
        cout<<"\nThe course "<<course->name<<" group"<<group<<" cannot be added because no teacher is teaching it"<<endl;
        return false;
    }

    LinkStudent*nn=new LinkStudent(group);
    nn->course=course;

    LinkStudent*temp=student->link;
    if(temp==NULL){
        student->link=nn;
        return true;
    }else{
        do{
            /*
             * Este ciclo al mismo tiempo que busca posicionarse en la ultima posición de la lista para agregar el
             * nuevo curso al estudiante también comprueba que el curso y grupo no se metan de manera repetida al
             * mismo estudiante, por eso es un ciclo do while
             */
            if(temp->course->code == nn->course->code && temp->group == nn->group){
                cout<<"This student has already assigned this group and course"<<endl;
                return false;
            }
            if(temp->next==NULL){
                break;
            }
            temp=temp->next;
        } while(temp != NULL);
        temp->next=nn;

        return true;
    }
}
bool searchiDMeeting(int idMeeting){
    Teachers*tempTeacher= firstTeacher;

    while(tempTeacher != NULL){


        /*
         * Ciclo para buscar que ID no este asignado a otra reunion
         * Este ciclo recorre cada profesor de la lista
         */

        LinkTeacher*tempLink=tempTeacher->link;
        while(tempLink != NULL){

            /*
             * Este ciclo recorre cada enlace a curso de profesor
             */

            Meeting*tempMeeting=tempLink->firstMeeting;
            while(tempMeeting != NULL){
                /*
                 * Este ciclo recorre cada reunion de de cada enlace de curso de profesor
                 */

                if(tempMeeting->id == idMeeting){

                    /*
                     * si el ID de la reunion es igual al ID que se quiere usar, es una restricción por tanto retorna false
                     * no se asigna la reuinión
                     */
                    cout<<"\nThere is another meeting with this ID assigned"<<endl;
                    return false;
                }
                tempMeeting=tempMeeting->next;
            }
            tempLink=tempLink->next;
        }
        tempTeacher=tempTeacher->next;
    }
    return true;
}

bool meetingTeacher(int idTeacher, string codeCourse,int group, int idMeeting, int hour, int minute, int hourE, int minuteE,int day, int month, int year, string titleMeeting){

    if(hourE< hour){
        cout<<"\nThe end time must be greater than the start time"<<endl;
        return false;
    }else if(hourE== hour && minuteE < minute){
        cout<<"\nThe end time must be greater than the start time"<<endl;
        return false;
    }

    Teachers*teacher=searchTeacher(idTeacher);//si retorna  NULL el teacher no existe, sino ya existe

    if(teacher == NULL){//esta el teacher
        cout<<"Teacher not found"<<endl;

        return false;
    }

    bool idFound=searchiDMeeting(idMeeting);

    if(idFound==false){
        return false;
    }

    LinkTeacher*temp= teacher->link;

    while(temp != NULL){

        /*
         * este ciclo recorre cada enlace de curso en busca del curso donde de debe asignar la reunion, sino encuentra
         * el enlace del curso es porque el curso no esta siendo impartido, por lo tanto no se puede asignar la reunion
         */

        if(temp->course->code == codeCourse && temp->group==group){

            Meeting*nn= new Meeting(idMeeting, hour, minute, hourE, minuteE, day, month, year, titleMeeting);
            if(temp->firstMeeting==NULL){
                temp->firstMeeting=nn;
                return true;
            }else{
                Meeting*temp2=temp->firstMeeting;
               do{
                    /*
                     * Este ciclo a parte de recorrer los enlaces de cursos verifica que el profesor no tenga otra
                     * reunión a la misma hora, el mismo día, mes y año
                     */

                    //comprueba que no se programe una reunionen el mismo tiempo que otra
                    if(temp2->year==nn->year && temp2->month == nn->month && temp2->day==nn->day && temp2->hour==nn->hour && temp2->minute==nn->minute){
                        cout<<"\nThe meeting cannot be assigned because this teacher already has a meeting at the same"<<
                        " time, day, month and year"<<endl;
                        return false;
                    }
                    //comprueba que no se programe una reunion cuando otra estará en curso
                   if(temp2->year==nn->year && temp2->month == nn->month && temp2->day==nn->day && temp2->hourEnd > nn->hour){
                       cout<<"\nYou cannot schedule the meeting because you will be in another meeting at that time"<<endl;
                       return false;
                   }
                   if(temp2->year==nn->year && temp2->month == nn->month && temp2->day==nn->day && temp2->hourEnd == nn->hour && temp2->minuteEnd > nn->minute){
                       cout<<"\nYou cannot schedule the meeting because you will be in another meeting at that time"<<endl;
                       return false;
                   }
                    if(temp2->next==NULL){
                        break;
                    }
                    temp2=temp2->next;
                }while(temp2 != NULL);
                temp2->next=nn;
                return true;
            }
        }
        temp=temp->next;
    }
    cout<<"The meeting cannot be assigned to this course because the teacher does not teach the course"<<endl;
    return false;
}

bool meetingStudent(int idStudent, string codeCourse, int courseGroup, int idMeeting){
    Students*student=searchStudent(idStudent);
    if(student==NULL){
        cout<<"\nStudent not found"<<endl;
        return false;
    }
    LinkStudent*temp=student->link;
    while(temp != NULL){
        /*
         * Este ciclo busca el enlace que tiene el curso y grupo para registrar la asistencia
         */
        if(temp->course->code==codeCourse && temp->group==courseGroup){
            Teachers*temp2=firstTeacher;
            while(temp2 != NULL){
                /*
                 * Este ciclo recorre la lista de profesores
                 */
                LinkTeacher*temp3=temp2->link;
                while(temp3 != NULL){
                    /*
                     * este ciclo recorre la lista de enlace del profesor
                     */
                    Meeting*temp4=temp3->firstMeeting;
                    while(temp4 != NULL){
                        /*
                         * este ciclo recorre la lista de reuniones que está en cada enlace de cada profesor
                         */
                        if(temp4->id==idMeeting){
                            /*
                             * si el id de la reuion es igual al pasado por parametro sí se asistió
                             */
                            bool verifyDate= searchDate(temp4);

                            if(verifyDate==true) {
                                cout << "5Attendance cannot be added because the meeting has not passed yet" << endl;
                                return false;
                            }
                            SublistAssistance* nn=new SublistAssistance(idMeeting);
                            if(student->link->sublistAssistance==NULL){
                                student->link->sublistAssistance=nn;
                                return true;
                            }else{
                                SublistAssistance*temp5=student->link->sublistAssistance;

                                while(temp5->next != NULL){
                                    temp5=temp5->next;
                                }
                                temp5->next=nn;
                                return true;
                            }
                        }
                        temp4=temp4->next;
                    }
                    temp3=temp3->next;
                }
                temp2=temp2->next;
            }

        }
        temp=temp->next;
    }
    /*
     * si se llega hasta aquí es porque no se encontro un el id de reunion por lo tanto no se participó
     */
    cout<<"\nThe student did not attend the meeting"<<endl;
    return false;
}

void modifyTeacherWoCourses(int id){ //Modifies a professor without an assigned course.

    Teachers*teacher = searchTeacher(id);
    if(teacher==NULL){
        cout<<"\nTeacher not found"<<endl;
        return;
    }
    if (teacher->link==NULL){
        string option;
        cout<<"\nThis is the information of this teacher:"<<endl;

        cout<<"Full name: "<<teacher->fullName<<"\nGender: "<<teacher->gender<<"\nId: "<<teacher->id<<endl;

        cout<<"What do you want to modify?\n1- Full name\n2- Gender\n3- ID"<<endl;

        cout<<"Select an option: ";

        cin>>option;

        if(option=="1"){

            string name;
            cout<<"\nWrite new full name: ";

            cin>>name;
            teacher->fullName=name;

            cout<<"\nModification successful!"<<endl;
            return;
        }else if(option=="2"){
            string gender;
            cout<<"\nWrite new gender: ";
            cin>>gender;

            teacher->gender=gender;

            cout<<"\nModification successful!"<<endl;

            return;
        }else if(option=="3"){

            int newId;

            while(true) {
                //Miestras el ID no sea válido se pedirá
                cout << "\nWrite new ID (only numbers): ";
                cin >> newId;
                Teachers *teacher2 = searchTeacher(newId);
                if (teacher2 == NULL) {
                    teacher->id=newId;
                    cout<<"\nModification successful!"<<endl;
                    return;
                }
                cout << "\nThis ID is not available, please try another" << endl;
            }
        }
    }
    else{
        cout<<"The professor already has courses assigned.";
        return;
    }
}
void modifyTeacherWithCourses(int id){ //Modifies a professor without an assigned course.

    Teachers*teacher = searchTeacher(id);
    if(teacher==NULL){
        cout<<"\nTeacher not found"<<endl;
        return;
    }
    if (teacher->link!=NULL){
        string option;
        cout<<"\nThis is the information of this teacher:"<<endl;

        cout<<"Full name: "<<teacher->fullName<<"\nGender: "<<teacher->gender<<"\nId: "<<teacher->id<<endl;

        cout<<"What do you want to modify?\n1- Full name\n2- Gender\n3- ID"<<endl;

        cout<<"Select an option: ";

        cin>>option;

        if(option=="1"){

            string name;
            cout<<"\nWrite new full name: ";

            cin>>name;
            teacher->fullName=name;

            cout<<"\nModification successful!"<<endl;
            return;
        }else if(option=="2"){
            string gender;
            cout<<"\nWrite new gender: ";
            cin>>gender;

            teacher->gender=gender;

            cout<<"\nModification successful!"<<endl;

            return;
        }else if(option=="3"){

            int newId;

            while(true) {
                //Miestras el ID no sea válido se pedirá
                cout << "\nWrite new ID (only numbers): ";
                cin >> newId;
                Teachers *teacher2 = searchTeacher(newId);
                if (teacher2 == NULL) {
                    teacher->id=newId;
                    cout<<"\nModification successful!"<<endl;
                    return;
                }
                cout << "\nThis ID is not available, please try another" << endl;
            }
        }
    }
    else{
        cout<<"The professor already has no courses assigned.";
        return;
    }

}
void deleteLinkCourseStudent(string code, int group=0){
    Students*temp=firstStudent;

    while(temp != NULL){

        LinkStudent*tempLink=temp->link;

        if(tempLink==NULL){
            temp = temp->next;
            continue;
        }else if((tempLink->course->code == code && tempLink->group == group) || (tempLink->course->code == code && group==0)){
            temp->link=temp->link->next;
        }else {
            tempLink = tempLink->next;
            LinkStudent *temp2 = temp->link;

            while (tempLink != NULL) {
                if ((tempLink->course->code == code && tempLink->group == group)||(tempLink->course->code == code && group==0)){
                    temp2->next=tempLink->next;
                    break;
                }
                temp2=temp2->next;
                tempLink=tempLink->next;
            }
        }
        temp = temp->next;
    }

}
bool deleteTeacherWoCourses(int id){
    Teachers*teacher= searchTeacher(id);
    if(teacher==NULL) {
        cout << "Teacher not found" << endl;
        return false;
    }
    if (teacher->link==NULL) {
        if (firstTeacher == teacher) {
            //Si el que se debe borrar es el primero de lista, solo se hace que el siguiente en previos apunte a NULL
            // y se redefine el firstTeacher como el segundo de la lista :)
            Teachers *temp = firstTeacher->next;
            temp->previous = NULL;
            firstTeacher = temp;
            cout << "\nDelete successful!" << endl;
            return true;
        } else if (teacher->next == NULL) {//Con el NULL no sirve, CLion me lo autocorrigió puso nullptr y sirvió
            //Si el que se debe borrar es el último de lista, solo se hace que el que está de penultimo apunte a NULL
            Teachers *temp2 = teacher->previous;
            temp2->next = NULL;
            cout << "\nDelete successful! central" << endl;
            return true;
        } else {
            //Si el que se debe borrar tiene anterior y siguiente diferentes de NULL, solo se hace que el anterior
            //apunte en next al que está apuntando el que se va a borrar en siguiente y ese siguinte en previous apunte
            //al que está antes del que se va a borrar, basicamente se deja de apuntar al que se va a borrar
            Teachers *temp3 = teacher->previous;
            Teachers *temp4 = teacher->next;
            temp3->next = temp4;
            temp4->previous = temp3;
            cout << "\nDelete successful! first" << endl;
            return true;
        }
    }
    else{
        cout<<"The professor already has courses assigned.";
        return false;
    }
}
bool deleteTeacherWithCourses(int id){
    Teachers*teacher= searchTeacher(id);
    if(teacher==NULL) {
        cout << "Teacher not found" << endl;
        return false;
    }
    if (teacher->link!=NULL) {
        LinkTeacher*courses=teacher->link;
        while(courses != NULL){
            //Ciclo que llama a funcion para borrar curso de estudiantes que imparte  el profesor a borrar
            deleteLinkCourseStudent(courses->course->code, courses->group);
            courses=courses->next;
        }
        if(teacher->next==NULL && teacher->previous==NULL){
            firstTeacher=NULL;
            cout<<"\nDeleted successfully!"<<endl;
            return true;
        }else if(firstTeacher==teacher){
            //Si el que se debe borrar es el primero de lista, solo se hace que el siguiente en previos apunte a NULL
            // y se redefine el firstTeacher como el segundo de la lista :)
            Teachers*temp=firstTeacher->next;
            temp->previous=NULL;
            firstTeacher=temp;
            cout<<"\nDeleted successfully!"<<endl;
            return true;
        } else if(teacher->next==NULL){//Con el NULL no sirve, CLion me lo autocorrigió puso nullptr y sirvió
            //Si el que se debe borrar es el último de lista, solo se hace que el que está de penultimo apunte a NULL
            Teachers*temp2=teacher->previous;
            temp2->next=NULL;
            cout<<"\nDeleted successfully!"<<endl;
            return true;
        }else{
            //Si el que se debe borrar tiene anterior y siguiente diferentes de NULL, solo se hace que el anterior
            //apunte en next al que está apuntando el que se va a borrar en siguiente y ese siguinte en previous apunte
            //al que está antes del que se va a borrar, basicamente se deja de apuntar al que se va a borrar
            Teachers*temp3=teacher->previous;
            Teachers*temp4=teacher->next;
            temp3->next=temp4;
            temp4->previous=temp3;
            cout<<"\nDeleted successfully!"<<endl;
            //print("professors");
            return true;
        }
    }
    else{
        cout<<"The professor does not have courses assigned.";
        return false;
    }
}
void modifyStudentWoCourses(int id){

    Students*student= searchStudent(id);

    if(student==NULL){
        cout<<"\nTeacher not found"<<endl;
        return;
    }
    if (student->link==NULL){
        string option;
        cout<<"\nThis is the information of this student:"<<endl;

        cout<<"Full name: "<<student->fullName<<"\nGender: "<<student->gender<<"\nId: "<<student->id<<endl;

        cout<<"What do you want to modify?\n1- Full name\n2- Gender\n3- ID"<<endl;

        cout<<"Select an option: ";

        cin>>option;

        if(option=="1"){
            string name;
            cout<<"\nWrite new full name: ";

            cin>>name;

            student->fullName=name;

            cout<<"\nModification successful!"<<endl;

            return;
        }else if(option=="2"){
            string gender;
            cout<<"\nWrite new gender: ";
            cin>>gender;

            student->gender=gender;

            cout<<"\nModification successful!"<<endl;

            return;
        }else if(option=="3"){

            int newId;

            while(true) {
                //Miestras el ID no sea válido se pedirá
                cout << "\nWrite new ID (only numbers): ";
                cin >> newId;
                Teachers *teacher2 = searchTeacher(newId);
                if (teacher2 == NULL) {
                    student->id=newId;
                    cout<<"\nModification successful!"<<endl;
                    return;
                }
                cout << "\nThis ID is not available, please try another" << endl;
            }
        }
    }
    else{
        cout<<"The student already has courses assigned.";
        return;
    }
}
void modifyStudentWithCourses(int id){

    Students*student= searchStudent(id);

    if(student==NULL){
        cout<<"\nTeacher not found"<<endl;
        return;
    }
    if (student->link!=NULL){
        string option;
        cout<<"\nThis is the information of this student:"<<endl;

        cout<<"Full name: "<<student->fullName<<"\nGender: "<<student->gender<<"\nId: "<<student->id<<endl;

        cout<<"What do you want to modify?\n1- Full name\n2- Gender\n3- ID"<<endl;

        cout<<"Select an option: ";

        cin>>option;

        if(option=="1"){
            string name;
            cout<<"\nWrite new full name: ";

            cin>>name;

            student->fullName=name;

            cout<<"\nModification successful!"<<endl;

            return;
        }else if(option=="2"){
            string gender;
            cout<<"\nWrite new gender: ";
            cin>>gender;

            student->gender=gender;

            cout<<"\nModification successful!"<<endl;

            return;
        }else if(option=="3"){

            int newId;

            while(true) {
                //Miestras el ID no sea válido se pedirá
                cout << "\nWrite new ID (only numbers): ";
                cin >> newId;
                Teachers *teacher2 = searchTeacher(newId);
                if (teacher2 == NULL) {
                    student->id=newId;
                    cout<<"\nModification successful!"<<endl;
                    return;
                }
                cout << "\nThis ID is not available, please try another" << endl;
            }
        }
    }
    else{
        cout<<"The student does not have courses assigned.";
        return;
    }
}
bool deleteStudentWithCourses(int id){

    Students*student=searchStudent(id);
    if(student==NULL){
        cout << "Student not found" << endl;
        return false;
    }
    if (student->link!=NULL){
        if(student==firstStudent){
            firstStudent=firstStudent->next;
            cout<<"\nDeleted successfully!"<<endl;
            return true;
        }

        Students*temp=firstStudent;

        while(temp->next != student){
            temp=temp->next;
        }
        temp->next=student->next;

        cout<<"\nDeleted successfully!"<<endl;
        return true;
    }
    else {
        cout << "The student does not have courses assigned.";
        return false;
    }
}
bool deleteStudentWoCourses(int id){

    Students*student=searchStudent(id);
    if(student==NULL){
        cout << "Student not found" << endl;
        return false;
    }
    if (student->link==NULL){
        if(student==firstStudent){
            firstStudent=firstStudent->next;
            cout<<"\nDeleted successfully!"<<endl;
            return true;
        }

        Students*temp=firstStudent;

        while(temp->next != student){
            temp=temp->next;
        }
        temp->next=student->next;

        cout<<"\nDeleted successfully!"<<endl;
        return true;
    }
    else {
        cout << "The student does not have courses assigned.";
        return false;
    }
}

void modifyCourse(string code){

    Courses*course= searchCourse(code);

    if(course==NULL){
        cout<<"\nTCourse not found"<<endl;
        return;
    }
    string option;
    cout<<"\nThis is the information of this course:"<<endl;

    cout<<"Name: "<<course->name<<"\nCredits: "<<course->credits<<"\nCode: "<<course->code<<endl;

    cout<<"What do you want to modify?\n1- Name\n2- Credits\n3- Code"<<endl;

    cout<<"Select an option: ";

    cin>>option;

    if(option=="1"){
        string name;
        cout<<"\nWrite new name: ";

        cin>>name;
        course->name=name;

        cout<<"\nModification successful!"<<endl;

        return;
    }else if(option=="2"){
        int credits;
        cout<<"\nWrite new credits number: ";
        cin>>credits;

        course->credits=credits;

        cout<<"\nModification successful!"<<endl;

        return;
    }else if(option=="3"){

        string code;

        while(true) {
            //Miestras el ID no sea válido se pedirá
            cout << "\nWrite new code: ";
            cin >> code;
            Courses*temp = searchCourse(code);
            if(temp == NULL) {
                course->code=code;
                cout<<"\nModification successful!"<<endl;
                return;
            }
            cout << "\nThis code is not available, please try another" << endl;
        }
    }
}

void deleteLinkCourseTeacher(string code){

    Teachers*temp=firstTeacher;

    while (temp != NULL){

        LinkTeacher*temp2=temp->link;

        if(temp2==NULL){
            return;
        }else if(temp2->course->code == code){
            temp->link=temp2->next;
            return;
        }else{
            LinkTeacher*temp3=temp->link;
            temp2=temp2->next;

            while(temp2 != NULL){
                if(temp2->course->code==code){
                    temp3->next=temp2->next;
                    return;
                }
                temp2=temp2->next;
                temp3=temp3->next;
            }
        }


        temp=temp->next;
    }

}

bool deleteCourse(string code){
    Courses*course= searchCourse(code);

    if(course==NULL){
        cout<<"\nCourse not found"<<endl;
        return false;
    }

    deleteLinkCourseTeacher(course->code);

    deleteLinkCourseStudent(course->code);


    Courses*temp=firstCourse;

    while (temp->next != course){
        temp=temp->next;
    }
    temp->next=course->next;

    if(course=firstCourse){
        firstCourse=course->next;
    }
    cout<<"\nDelete successful!"<<endl;
    return true;
}

void print(string n){
    //cout << "--------Print Menu--------" << endl;
    //cout << "Type 1- for teachers" << endl;
    //cout << "Type 2- for Students" << endl;
    //cout << "Type 3- for courses" << endl;
    //cout << "Type 4- for EXIT" << endl;
    //int num;
    //cout << "\nType the number on your keyboard of the option you want to execute: ";
    //cin >> num;
    if (n == "professors") {
        cout<<"\n-----Professors-----\n";
        Teachers*temp=firstTeacher;

        while(temp != NULL){
            cout<<"\n"<<temp->fullName<<endl;
            LinkTeacher*temp2=temp->link;
            while(temp2 != NULL){
                cout<<temp2->course->name<<endl;
                temp2=temp2->next;
            }
            temp=temp->next;
        }
    }
    else if (n == "students") {
        cout<<"\n-----Students-----\n";

        Students*temp3=firstStudent;

        while(temp3 != NULL){
            cout<<"\n"<<temp3->fullName<<endl;
            LinkStudent*temp4= temp3->link;
            while(temp4 != NULL){
                cout<<temp4->course->name<<endl;
                temp4=temp4->next;
            }
            temp3=temp3->next;

        }
    }
    else if (n == "courses") {
        cout << "\n-----Courses-----\n";

        Courses *course = firstCourse;

        do {
            cout << course->name << "---" << course->code << endl;
            course = course->next;
        } while (course != firstCourse);
    }
    /*else if (num == 4) {
        cout<<"Thanks for using our platform!"<<endl;
        return;
    }*/
}

bool searchDate(Meeting*meet){
    /*
    int yr=2021;
    int mth=04;
    int dy=04;
    int hr=17;
    int mins=00;
     */

    //retorna false si reunion ya pasó  y retorna true si no ha pasado

    if(meet->year > yr)
        return true;
    if(yr==meet->year && meet->month > mth)
        return true;
    if(yr==meet->year && meet->month < mth)
        return false;
    if(mth==meet->month && meet->day> dy)
        return true;
    if(mth==meet->month && meet->day < dy)
        return false;
    if(dy==meet->day && meet->hour> hr)
        return true;
    if(dy==meet->day && meet->hour< hr)
        return false;
    if(hr==meet->hour && meet->minute > mins)
        return true;
    return false;

}

void deleteMeetingOfTeacher(int idTeacher,string codeCourse, int groupCourse){

    Teachers*teacher=searchTeacher(idTeacher);

    if(teacher== NULL){
        cout<<"Teacher not found"<<endl;
        return;
    }
    LinkTeacher*linkTeacher=teacher->link;

    if(linkTeacher == NULL){
        cout<<"\nThis teacher has not asignnated courses"<<endl;
        return;
    }else {
        while (linkTeacher != NULL) {
            if (linkTeacher->course->code == codeCourse && linkTeacher->group == groupCourse) {
                break;
            }
            linkTeacher = linkTeacher->next;
        }
        if (linkTeacher == NULL) {
            cout << "\nThis teacher has no asignnated that course" << endl;
            return;
        } else {
            Meeting *meet = linkTeacher->firstMeeting;
            if (meet == NULL) {
                cout << "\nThis teacher has no meetings programmed for this course" << endl;
                return;
            }
            cout << "\nThis are the meetings programmed for this course" << endl;
            bool flag = false;
            while (meet != NULL) {
                bool printMeeting = searchDate(meet);
                if (printMeeting == true) {
                    flag = true;
                    cout << "\nID: " << meet->id << "\nTitle: " << meet->meetingTitle << "\nStart date: " << meet->day
                         << "/" << meet->month << "/" << meet->year << "\nStart hour: " << meet->hour << ":"
                         << meet->minute <<
                         "\nFinish hour: " << meet->hourEnd << ":" << meet->minuteEnd << endl;
                }
                meet = meet->next;
            }
            if (flag == false) {
                cout << "This teacher has no future meetings for this course" << endl;
                return;
            }
            int option;
            cout << "\nEnter the ID of the meeting to delete: ";

            cin >> option;

            Meeting*meet2=linkTeacher->firstMeeting;

            if(meet2->id==option){
                linkTeacher->firstMeeting=meet2->next;
                cout<<"\nMeeting deleted successfully"<<endl;
                return;
            }
            Meeting*meet3;
            while(meet2->id != option){
                meet3=meet2;
                meet2=meet2->next;
            }
            meet3->next=meet2->next;

            cout<<"\nMeeting deleted successfully"<<endl;

            return;
        }
    }
}

void modifyMeetingOfTeacher(int id, string code, int group){

    Teachers*teacher=searchTeacher(id);

    if(teacher== NULL){
        cout<<"\nTeacher not found"<<endl;
        return;
    }

    LinkTeacher*linkTeacher=teacher->link;

    if(linkTeacher == NULL){
        cout<<"\nThis teacher has not asignnated courses"<<endl;
        return;
    } else{
        while(linkTeacher != NULL){
            if(linkTeacher->course->code==code && linkTeacher->group==group){
                break;
            }
            linkTeacher=linkTeacher->next;
        }
        if(linkTeacher==NULL){
            cout<<"\nThis teacher has no asignnated that course"<<endl;
            return;
        }else{
            Meeting*meet=linkTeacher->firstMeeting;
            if(meet==NULL){
                cout<<"\nThis teacher has no meetings programmed for this course"<<endl;
                return;
            }
            cout<<"\nThis are the meetings programmed for this course"<<endl;
            bool flag=false;
            while(meet != NULL){
                bool printMeeting=searchDate(meet);
                if(printMeeting==true) {
                    flag=true;
                    cout << "\nID: " << meet->id << "\nTitle: " << meet->meetingTitle << "\nStart date: " << meet->day
                    << "/" <<meet->month << "/" << meet->year << "\nStart hour: " << meet->hour << ":" << meet->minute <<
                    "\nFinish hour: " << meet->hourEnd << ":" << meet->minuteEnd << endl;
                }
                meet=meet->next;
            }
            if(flag==false){
                cout<<"This teacher has no future meetings for this course"<<endl;
                return;
            }
            int option;
            cout<<"\nEnter the ID of the meeting to modify: ";

            cin>>option;
            Meeting*meet2=linkTeacher->firstMeeting;
            while(meet2->id != option){
                meet2=meet2->next;
            }
            cout<<"\nWhat do you want to modify?\n1- ID\n2- Title\n3- Date\n\nSelect an option: ";

            string option2;
            cin>>option2;

            if(option2=="1"){
                while(true) {
                    cout << "\nWrite the new ID: ";
                    cin>>option;

                    if(searchiDMeeting(option)==false){
                        cout<<"\nThis ID is not available, try another"<<endl;
                    }else{
                        meet2->id=option;
                        cout<<"\nSuccessful modification"<<endl;
                        return;
                    }
                }
            }else if(option2=="2"){
                string newTitle;
                cout<<"\nWrite the new title: ";
                cin>>newTitle;

                meet2->meetingTitle=newTitle;

                cout<<"\nSuccessful modification"<<endl;
                return;
            }else if(option2=="3"){

                while(true) {

                    bool invalide=true;
                    int hour = 0;
                    char c;
                    int minutes = 0;
                    char d;
                    int day = 0;
                    int mounth = 0;
                    int year = 0;
                    char a;
                    char b;

                    cout << "\nWrite de new date (for examanple: 15:20/29/03/2021): ";

                    cin >> hour >> c >> minutes >> d >> day >> a >> mounth >> b >> year;

                    if (hour >= 0 && hour <= 23 && c == ':' && minutes >= 0 && minutes <= 59 && d == '/' && day > 0 &&
                        day < 32 &&
                        a == '/' && mounth > 0 && mounth < 13 && b == '/' && year > 2020 && year < 2022) {

                        int hourE;
                        int minuteE;

                        cout << "\nWrite de new final hour meeting (for examanple: 15:20): ";

                        cin >> hourE >> c >> minuteE;

                        LinkTeacher*temp=teacher->link;

                        while(temp != NULL) {

                            Meeting*temp2=temp->firstMeeting;

                            while (temp2 != NULL) {
                                /*
                                 * Este ciclo a parte de recorrer los enlaces de cursos verifica que el profesor no tenga otra
                                 * reunión a la misma hora, el mismo día, mes y año
                                 */

                                //comprueba que no se programe una reunionen el mismo tiempo que otra
                                if (temp2->year == year && temp2->month == mounth && temp2->day == day &&
                                    temp2->hour == hour && temp2->minute == minutes) {
                                    cout<< "\nThe meeting cannot be assigned because this teacher already has a meeting at the same"<<
                                    " time, day, month and year" << endl;
                                    invalide=false;
                                    break;
                                }
                                //comprueba que no se programe una reunion cuando otra estará en curso

                                if (temp2->year == year && temp2->month == mounth && temp2->day == day &&
                                    temp2->hourEnd > hour) {
                                    cout<< "\nYou cannot schedule the meeting because you will be in another meeting at that time"<< endl;
                                    invalide=false;
                                    break;
                                }
                                if (temp2->year == year && temp2->month == mounth && temp2->day == day &&
                                    temp2->hourEnd == hour && temp2->minuteEnd > minuteE) {
                                    cout<< "\nYou cannot schedule the meeting because you will be in another meeting at that time"<< endl;
                                    invalide=false;
                                    break;
                                }
                                temp2 = temp2->next;
                            }

                            if(invalide== false) {
                                break;
                            }

                            temp=temp->next;
                        }
                        if(invalide== false) {
                            continue;
                        }

                        if (hourE < hour) {
                            cout << "\nThe end time must be greater than the start time" << endl;
                            continue;
                        } else if (hourE == hour && minuteE < minutes) {
                            cout << "\nThe end time must be greater than the start time" << endl;
                            continue;
                        }
                        meet2->hour=hour, meet2->year=year, meet2->minute=minutes, meet2->day=day;
                        meet2->month=mounth, meet2->minuteEnd=minuteE, meet2->hourEnd=hourE;

                        cout<<"\nSuccessful modification"<<endl;
                        return;

                    } else {
                        cout << "Incorrect format: HHHH/DD/MM/AAAA";
                    }
                }
            }
        }
    }
}

void HardCode(){

    //agergar profes

    addTeacher("Lorena Picado", 1, "Female");
    addTeacher("Abel Mendez", 2, "Male");
    addTeacher("Rocio Aguilar", 3, "Female");
    addTeacher("Vera Gamboa", 4, "Female");
    addTeacher("Karina Gonzales", 5, "Female");
    //addTeacher("Oscar Viquez", 6, "Male");
    //agregar estudiantes

    addStudent("Alonso Martinez", 5, "Male");
    addStudent("Estefania Perez", 2, "Female");
    addStudent("Luz Mora", 3, "Female");
    addStudent("Bryam Lopez", 1, "Male");
    addStudent("Josue Orozco", 4, "Male");
    addStudent("Fernanda Chavez", 6, "Female");

    //agregar cursos

    addCourse("Estructura de Datos", "CA1101", 3);
    addCourse("Programacion Orientada a Objetos", "CA1298", 3);
    addCourse("Calculo Diferencial e Integral", "MA1226", 4);
    addCourse("Matematicas Discretas", "MA7878", 4);
    addCourse("Arquitectura de Computadores", "CA1103", 4);
    addCourse("Introduccion a la Programacion", "CA1558", 3);

    //agergar admins

    addAdmin("Veronica Brenes", 1, "Female");
    addAdmin("Christian Gonzales", 2, "Male");
    addAdmin("Monica Speer", 3, "Female");
    addAdmin("Julio Cesar", 4, "Male");
    addAdmin("Sonia Rojas", 5, "Female");

    //Relacionar profesor con curso

    relateTeacherCourse(5, "MA7878", 53);
    relateTeacherCourse(2, "CA1558", 50);
    relateTeacherCourse(1, "CA1101", 51);
    relateTeacherCourse(3, "CA1103", 52);
    relateTeacherCourse(4, "CA1298", 52);
    relateTeacherCourse(5, "MA1226", 51);
    relateTeacherCourse(5, "MA1226", 53);

    //Relacionar estudiante con curso

    relateStudentCourse(5, "MA1226", 51);
    relateStudentCourse(5, "CA1101", 51);
    relateStudentCourse(2, "CA1101", 51);
    relateStudentCourse(2, "MA7878", 53);
    relateStudentCourse(3, "CA1558", 50);
    relateStudentCourse(4, "CA1101", 51);
    relateStudentCourse(1, "CA1103", 52);
    relateStudentCourse(1, "CA1298", 52);
    relateStudentCourse(1, "MA1226", 51);

    //Asignar reunión a un profesor
    meetingTeacher(5, "MA1226",51 ,1,  13, 10, 16, 55,18, 04, 2021,  "clase magistral");
    meetingTeacher(5, "MA1226",51,2,  16, 55, 18, 30,22, 04, 2021,  "clase magistral");
    meetingTeacher(5, "MA1226",53,7,  15, 10, 19, 30,23, 04, 2021,  "clase magistral");
    meetingTeacher(4, "CA1298",52,3,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");
    meetingTeacher(3, "CA1103",52 ,4,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");
    meetingTeacher(2, "CA1558",50 ,5,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");
    meetingTeacher(1, "CA1101",51 ,6,  7, 50, 11, 30, 29, 03, 2021,  "clase magistral");
    meetingTeacher(5, "MA1226",51 ,8,  13, 10, 16, 55,18, 03, 2021,  "clase magistral");
    meetingTeacher(5, "MA1226",51,9,  16, 55, 18, 30,22, 03, 2021,  "clase magistral");

    //Estudiantes indican reunion en la que participaron

    meetingStudent(5, "MA1226", 51, 8);
    meetingStudent(5, "MA1226", 51, 9);
    meetingStudent(1, "MA1226", 51, 9);


    //----Modificar profesor------

    //modifyTeacher(5);


    //------Delete teacher------

    //deleteTeacher(1);


    //------Modificar estudiante------

    //modifyStudent(5);


    //------Borrar estudiante------
    //deleteStudent(1);


    //------Modificar curso------

    //modifyCourse("CA1298");

    //modifyCourse("CA1558");


    //------Borrar curso------

    //deleteCourse("CA1101");
    //print();


    //Modificar reunión de profesor

    //deleteMeetingOfTeacher(5,"MA1226", 51);
    //modifyMeetingOfTeacher(5, "MA1226", 51);

}
void viewNextMeetings(Teachers*teacher){

    int contador=7;


    if(teacher->link!=NULL){
        cout<<"\n\tThis are the meetings for the next week:\n";
        while(contador<=13){
            LinkTeacher*temp=teacher->link;

            int mounthM=mth;
            int dayM=dy+contador;
            int yearM=yr;
            if(dayM>32){
                dayM=dayM-32;
                mounthM=mth+1;
                if(mounthM>12){
                    mounthM=mounthM-12;
                    yearM=yr+1;
                }
            }
            cout<<"\n"<<dayM<<"/"<<mounthM<<"/"<<yearM<<":";
            bool print=false;

            while(temp!= NULL){

                Meeting*temp2=temp->firstMeeting;

                while(temp2 != NULL){

                    if(temp2->year=yearM && temp2->month==mounthM && temp2->day==dayM){
                        print=true;

                        cout<<"\n\tMeeting at "<<temp2->hour<<":"<<temp2->minute<<" of "<<temp->course->name<<" group "<<temp->group<<endl;

                    }

                    temp2=temp2->next;
                }

                temp=temp->next;
            }
            if(!print)
                cout<<"\nThere aren't meetings scheduleds for these day"<<endl;

            contador++;

        }
    }
}

void viewAssists(Teachers*teacher){

    LinkTeacher*temp=teacher->link;

    while(temp != NULL){


        Meeting*temp2=temp->firstMeeting;

        while(temp2 != NULL){



            if(searchDate(temp2)==false) {

                queue<string>ausentes;

                cout << "\nMeenting " << temp2->day << "/" << temp2->month << "/" << temp2->year << " at "
                     << temp2->hour << ":" << temp2->minute << " " << temp->course->name;

                cout << "\nattended:" << endl;

                Students*students = firstStudent;
                bool print=false;
                while (students != NULL) {

                    bool asiste=false;
                    LinkStudent*courses = students->link;

                    if(courses==NULL){
                        students=students->next;
                        continue;
                    }

                    while (courses != NULL) {

                        SublistAssistance*assistance = courses->sublistAssistance;


                        while (assistance != NULL) {

                            if (assistance->id == temp2->id) {
                                print=true;
                                asiste=true;
                                cout <<"\t"<<students->fullName << endl;
                            }

                            assistance = assistance->next;
                        }
                        if(courses->course->code==temp->course->code && courses->group==temp->group){
                            if(asiste==false){
                                ausentes.push(students->fullName);
                            }
                        }

                        courses = courses->next;
                    }

                    students = students->next;
                }
                if(print==false){
                    cout<<"\n\tNobody attended"<<endl;
                }

                cout<<"\nNot attended:"<<endl;

                if(ausentes.size()!=0){
                    while(ausentes.size()!=0){
                        cout<<"\t"<<ausentes.back()<<endl;
                        ausentes.pop();
                    }
                }else{
                    cout<<"\tAll attended"<<endl;
                }

            }

            temp2 = temp2->next;
        }
        temp=temp->next;
    }
}

//-----------------------
//ARRIBA DEL MÉTODO MEETINGSTUDENT ESTAN VARIABLES SIMULANDO UNA FECHA, PARA NO ESTAR INGRESANDO POR CONSOLA TANTO
//-------------------------

void menu(){

    while(true) {
        cout << "--------Option Menu--------" << endl;
        cout << "Type 1- for teachers" << endl;
        cout << "Type 2- for Students" << endl;
        cout << "Type 3- for Administrators" << endl;
        cout << "Type 4- for EXIT" << endl;
        int num;
        cout << "\nType the number on your keyboard of the option you want to execute: ";
        cin >> num;
        string codeCourse;
        int group;
        int idMeeting;
        if (num == 1) {
            int idTeacher;
            cout << "\nType your ID Teacher: ";
            cin >> idTeacher;
            Teachers*teacher = searchTeacher(idTeacher);
            if (teacher != NULL) {
                while(true) {
                    cout << "\n-------WELCOME TO THE TEACHER PLATFORM--------" << endl;
                    cout << "Type 1- To insert a meeting to a course" << endl;
                    cout << "Type 2- To modify a course meeting" << endl;
                    cout << "Type 3- To delete a course meeting" << endl;
                    cout << "Type 4- View meetings for next week" << endl;
                    cout << "Type 5- View attendance of meetings already held" << endl;
                    cout << "Type 7- To go back to main menu" << endl;

                    string optionTeacher;
                    cout << "\nType the option: ";
                    cin >> optionTeacher;
                    if (optionTeacher == "1") {
                        int hour;
                        int minute;
                        int hourE;
                        int minuteE;
                        int day;
                        int month;
                        int year;
                        string titleMeeting;
                        cout << "\nEnter the code of the Course class to be scheduled: ";
                        cin >> codeCourse;
                        cout << "\nEnter the group of the Course class to be scheduled: ";
                        cin >> group;
                        cout << "\nEnter the Meeting ID of the class to be scheduled: ";
                        cin >> idMeeting;

                        while (true) {
                            cin.ignore();
                            cout << "\nEnter the date Meeting of the class to be scheduled (example 18:10/11/05/2021): "<<endl;
                            cin >> hour >> c >> minute >> d >> day >> a >> month >> b >> year;
                            if (hour >= 0 && hour <= 23 && c == ':' && minute >= 0 && minute <= 59 && d == '/' &&
                                day > 0 && day < 32 && a == '/' && month > 0 && month < 13 && b == '/' &&
                                year > 2020 && year < 2022) {

                                cout << "\nEnter the date meeting of the class to be scheduled (example 18:10): ";

                                cin >> hourE >> c >> minuteE;
                                if (hourE >= 0 && hourE <= 23 && c == ':' && minuteE >= 0 && minuteE <= 59) {
                                    break;
                                }

                            } else {
                                cout << "\nWrong Format: HHHH/DD/MM/AAAA";
                            }
                        }

                        cout << "\nEnter a name for the meeting to be scheduled: ";
                        cin.ignore();
                        getline(cin, titleMeeting);

                        bool meeting = meetingTeacher(idTeacher, codeCourse,group, idMeeting, hour, minute, hourE, minuteE, day, month, year, titleMeeting);
                        if (meeting)
                            cout << "\nThe meeting was inserted successfully." << endl;
                        else
                            cout << "\nERROR! The meeting was not inserted." << endl;

                    } else if (optionTeacher == "2") {
                        cout << "\nEnter the course code: ";
                        cin >> codeCourse;
                        cout << "\nEnter the group number: ";
                        cin >> group;
                        modifyMeetingOfTeacher(idTeacher, codeCourse, group);


                    } else if (optionTeacher == "3") {

                        cout << "\nEnter the course code: ";
                        cin >> codeCourse;
                        cout << "\nEnter the group number: ";
                        cin >> group;

                        deleteMeetingOfTeacher(idTeacher, codeCourse, group);
                    }else if (optionTeacher == "4") {


                            viewNextMeetings(teacher);

                    }else if (optionTeacher == "5") {


                        viewAssists(teacher);

                    }else if(optionTeacher == "7") {

                        menu();
                    } else
                        cout << "ERROR! The typed option does not exist" << endl;

                }
            } else
                cout<<"Your teacher ID  is not registered on the platform" << endl;
        }
        else if (num == 2){
            int IDStudent;
            cout << "\nType your ID Studen: ";
            cin >> IDStudent;
            Students *student = searchStudent(IDStudent);//si retorna  NULL el estudiante no existe, sino ya existe
            if (student != NULL) {
                while(true) {
                    cout << "\n-------WELCOME TO THE STUDENT PLATFORM--------" << endl;
                    cout << "Type 1- Course meeting attendance record" << endl;
                    cout << "Type 2- Back to Main Menu" << endl;
                    int OptionStudent;
                    cout << "\n Type the option: ";
                    cin >> OptionStudent;
                    if (OptionStudent == 1) {
                        cout << "Enter the Course code" << endl;
                        cin >> codeCourse;
                        cout << "Enter the group number" << endl;
                        cin >> group;
                        cout << "Enter the meeting's ID of the course" << endl;
                        cin >> idMeeting;
                        meetingStudent(IDStudent, codeCourse, group, idMeeting);
                    }else if(OptionStudent==2)
                        break;

                    else
                        cout << "ERROR! The typed option does not exist." << endl;
                }
            } else{
                cout<<"Your Student ID is not registered on the platform" << endl;
                return;}
        }
        else if (num == 3){
            int IDadm;
            string fullName;
            cout << "Type your Administrator ID: ";
            cin >> IDadm;
            cin.ignore();
            cout << "\nType your Full Name: ";
            getline(cin, fullName);
            Administrators*admin=searchAdmin(fullName, IDadm);
            if(admin != NULL){
                    cout << "\n--------WELCOME TO THE ADMINISTRATOR PLATFORM--------" << endl;
                    cout << "Type -1- To perform actions on teachers with no assigned courses" << endl;
                    cout << "Type -2- To perform actions on students with no assigned courses" << endl;
                    cout << "Type -3- To perform actions on courses" << endl;
                    cout << "Type -4- To perform actions on teachers with assigned courses" << endl;
                    cout << "Type -5- To perform actions on students with assigned courses" << endl;
                    int Option;
                    cout << "\nType the number of the option you want to execute on your keyboard" << endl;
                    cin >> Option;
                    char Options;
                    string fullname;
                    int Id;
                    string gender;
                    if(Option == 1){
                        cout << "Type a- To Insert teachers" << endl;
                        cout << "Type b- To Delete teachers" << endl;
                        cout << "Type c- To Modify teachers with no assigned courses" << endl;
                        cout << "Type the letter of the option: ";
                        cin>>Options;
                        if(Options == 'a'){
                            cout<<"\nInsert the full name of the teacher"<<endl;
                            cin.ignore();
                            getline(cin, fullname);
                            cout<<"Insert the teacher ID"<<endl;
                            cin>>Id;
                            cout<<"Insert the gender of the teacher"<<endl;
                            cin>>gender;
                            bool result = addTeacher(fullname, Id, gender);
                            if(result == true){
                                cout<<"The teacher was added successfully"<<endl;
                                updateTeachersList();
                            }
                            else
                                cout<<"The teacher was not added correctly"<<endl;
                        }
                        else if(Options == 'b'){
                            cout<<"Insert the teacher ID"<<endl;
                            cin>>Id;
                            bool result = deleteTeacherWoCourses(Id);
                            if(result == true){
                                cout<<"The teacher was deleted successfully"<<endl;
                            }
                            else
                                cout<<"The teacher was not removed correctly"<<endl;
                        }
                        else if(Options == 'c'){
                            cout<<"Insert the teacher ID"<<endl;
                            cin>>Id;
                            modifyTeacherWoCourses(Id); //****************************************************
                        }
                        else{
                            cout<<"ERROR!!, The typed option does not exist"<<endl;
                            return;
                        }
                    }
                    else if(Option == 2){
                        cout << "Type -a- To Insert students" << endl;
                        cout << "Type -b- To Delete students" << endl;
                        cout << "Type -c- To Modify students" << endl;
                        cout << "Type the letter of the option"<<endl;
                        cin>>Options;
                        if(Options == 'a'){
                            cout<<"Insert the full name of the student"<<endl;
                            cin>>fullname;
                            cout<<"Insert the student ID"<<endl;
                            cin>>Id;
                            cout<<"Insert the gender of the student"<<endl;
                            cin>>gender;
                            bool result = addStudent(fullname, Id, gender);
                            if(result == true){
                                cout<<"The student was added successfully."<<endl;
                            }
                            else
                                cout<<"The student was not added correctly."<<endl;
                        }
                        else if(Options == 'b'){
                            cout<<"Insert the Student ID"<<endl;
                            cin>>Id;
                            bool result = deleteStudentWoCourses(Id);
                            if(result == true){
                                cout<<"The student was deleted successfully."<<endl;
                            }
                            else
                                cout<<"The student was not removed."<<endl;

                        }
                        else if(Options == 'c'){
                            cout<<"Insert the student ID"<<endl;
                            cin>>Id;
                            modifyStudentWoCourses(Id);  //****************************************************
                        }
                        else{
                            cout<<"ERROR!!, The typed option does not exist"<<endl;
                            return;
                        }
                    }
                    else if(Option == 3){
                        cout << "Type -a- To Insert courses" << endl;
                        cout << "Type -b- To Delete courses" << endl;
                        cout << "Type -c- To Modify courses" << endl;
                        cout << "Type the letter of the option"<<endl;
                        cin>>Options;
                        string code;
                        if(Options == 'a'){
                            string name;
                            int credits;
                            cout<<"Insert the name of the course"<<endl;
                            cin>>name;
                            cout<<"Insert the code of the course"<<endl;
                            cin>>code;
                            cout<<"Insert the credits of the course"<<endl;
                            cin>>credits;
                            bool result = addCourse(name, code, credits);
                            if(result == true){
                                cout<<"The course was added successfully"<<endl;
                            }
                            else
                                cout<<"The course was not added correctly"<<endl;
                        }
                        else if(Options == 'b'){
                            cout<<"Insert the code of the course"<<endl;
                            cin>>code;
                            bool result = deleteCourse(code);
                            if(result == true){
                                cout<<"The course was deleted successfully"<<endl;
                            }
                            else
                                cout<<"The course was not removed correctly"<<endl;

                        }
                        else if(Options == 'c'){
                            cout<<"Insert the code of the course"<<endl;
                            cin>>code;
                            modifyCourse(code);
                        }
                        else{
                            cout<<"ERROR! The typed option does not exist"<<endl;
                            return;
                        }
                    }
                    else if(Option == 4){
                        cout << "Type -a- To Insert teachers with courses" << endl;
                        cout << "Type -b- To Delete teachers with courses" << endl;
                        cout << "Type -c- To Modify teachers with courses" << endl;
                        cout << "Type the letter of the option"<<endl;
                        cin>>Options;
                        if(Options == 'b'){
                            cout<<"Insert the teacher ID"<<endl;
                            cin>>Id;
                            deleteTeacherWithCourses(Id); //****************************************************
                        }
                        else if(Options == 'c'){
                            cout<<"Insert the teacher ID"<<endl;
                            cin>>Id;
                            modifyTeacherWithCourses(Id); //****************************************************
                            }
                        else {
                            cout << "ERROR! The typed option does not exist" << endl;
                            return;
                        }
                    }
                    else if(Option == 5){
                        cout << "Type -a- To Insert students with courses" << endl;
                        cout << "Type -b- To Delete students with courses" << endl;
                        cout << "Type -c- To Modify students with courses" << endl;
                        cout << "Type the letter of the option"<<endl;
                        cin>>Options;
                        if(Options == 'b'){
                            cout<<"Insert the teacher ID"<<endl;
                            cin>>Id;
                            deleteStudentWithCourses(Id); //****************************************************
                        }
                        else if(Options == 'c'){
                            cout<<"Insert the teacher ID"<<endl;
                            cin>>Id;
                            modifyStudentWithCourses(Id); //****************************************************
                        }
                        else {
                            cout << "ERROR! The typed option does not exist" << endl;
                            return;
                        }
                    }
                    else {
                        cout << "ERROR! The typed option does not exist" << endl;
                        return;
                    }
            }
            else{
                cout << "\nYour Administrator ID is not registered on the platform." << endl;
                return;}
        }
        else if (num == 4){
            cout<<"Thanks for using our platform!"<<endl;
            break;
        }
    }

}

int main() {

    while(true) {
        hr=00;
        cout<<"Please, type your current time (format: HHHH/DD/MM/AAAA; e.i: 15:20/29/03/2021): " ;
        cin >> hr >> c >> mins >> d >> dy >> a >> mth >> b >> yr;

        if (hr >= 00 && hr <= 23 && c == ':' && mins >= 0 && mins <= 59 && d == '/' && dy > 0 && dy < 32 && a == '/' && mth > 0 && mth < 13 && b == '/' && yr > 2020 && yr < 2022) {
            cout << "\nThe date is correct." << endl;
            break;
        }else{
            cout << "Wrong Format: HHHH/DD/MM/AAAA"<<endl;
        }
        continue;
    }
    HardCode();
    menu();
    //updateTeachersList();

    /*

    updateStudentsList();
    */

    return 0;
}