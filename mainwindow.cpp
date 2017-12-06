#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    name[1] = "huochuan";
    name[2] = "youlun";
    name[3] = "youting";
    name[4] = "yuchuan";
    id["huochuan"] = 1;
    id["youlun"] = 2;
    id["youting"] = 3;
    id["yuchuan"] = 4;
    freopen("/home/yurikaka/Downloads/fangyi/result-v4/result_without_dup.txt","r",stdin);
    int x1, x2, y1, y2;
    string label, line, file, tmp;
    while (getline(cin,line)) {
        stringstream ss;
        ss.str(line);
        ss >> tmp >> y1 >> x2 >> y2;
        file = tmp.substr(0,6);
        int pos = tmp.rfind(',');
        x1 = stoi(tmp.substr(pos+1));
        label = tmp.substr(11,pos-11);
        mp[stoi(file)].push_back({id[label],x1,y1,x2,y2});
    }
    ifstream ans("/home/yurikaka/Downloads/fangyi/result-v4/order.txt");
    while (getline(ans,line)) {
        stringstream ss;
        ss.str(line);
        ss >> tmp >> y1 >> x2 >> y2;
        file = tmp.substr(0,6);
        int pos = tmp.rfind(',');
        x1 = stoi(tmp.substr(pos+1));
        label = tmp.substr(11,pos-11);
        mp_ans[stoi(file)].push_back({id[label],x1,y1,x2,y2});
    }
    ifstream wrong("/home/yurikaka/Downloads/fangyi/result-v4/wrong.txt");
    while (getline(wrong,line)) {
        stringstream ss;
        ss.str(line);
        ss >> tmp >> y1 >> x2 >> y2;
        file = tmp.substr(0,6);
        int pos = tmp.rfind(',');
        x1 = stoi(tmp.substr(pos+1));
        label = tmp.substr(11,pos-11);
        mp_wrong[stoi(file)].push_back({id[label],x1,y1,x2,y2});
    }
    ifstream miss("/home/yurikaka/Downloads/fangyi/result-v4/miss.txt");
    while (getline(miss,line)) {
        stringstream ss;
        ss.str(line);
        ss >> tmp >> y1 >> x2 >> y2;
        file = tmp.substr(0,6);
        int pos = tmp.rfind(',');
        x1 = stoi(tmp.substr(pos+1));
        label = tmp.substr(11,pos-11);
        mp_miss[stoi(file)].push_back({id[label],x1,y1,x2,y2});
    }
    this->resize(1200,1050);
    num = 0;
    lab = new QLabel(this);
    lab->move(10,10);
    cur = new QLineEdit(this);
    cur->move(1050,50);
    go = new QPushButton("go",this);
    go->move(1050,110);
    last = new QPushButton("last",this);
    last->move(1050,170);
    next = new QPushButton("next",this);
    next->move(1050,230);
    img = new QImage;
    show_img();
    connect(next,SIGNAL(clicked(bool)),this,SLOT(on_clicked_next()));
    connect(last,SIGNAL(clicked(bool)),this,SLOT(on_clicked_last()));
    connect(go,SIGNAL(clicked(bool)),this,SLOT(on_clicked_go()));
}

void MainWindow::show_img() {
    QString filename = QString::fromStdString(to_string(num+1));
    cur->setText(filename);
    while (filename.size() < 6)
        filename = "0" + filename;
    filename = "/home/yurikaka/Downloads/fangyi/test-v3-judge/" + filename + ".jpg";
    this->setWindowTitle("img_label  "+filename);
    lab->setText(filename);
    img->load(filename);
    QPainter p(img);
    QPen pen;
    pen.setWidth(3);
    pen.setBrush(Qt::white);
    p.setPen(pen);
    for (auto i : mp[num+1]) {
        p.drawRect(i[1],i[2],i[3]-i[1],i[4]-i[2]);
        p.drawText(i[1]+3,i[2]+3,i[3]-i[1],20,Qt::AlignLeft,name[i[0]]);
    }
    pen.setBrush(Qt::green);
    p.setPen(pen);
    for (auto i : mp_ans[num+1]) {
        p.drawRect(i[1],i[2],i[3]-i[1],i[4]-i[2]);
        p.drawText(i[1]+3,i[4]+3,i[3]-i[1],20,Qt::AlignLeft,name[i[0]]);
    }
    pen.setBrush(Qt::red);
    p.setPen(pen);
    for (auto i : mp_wrong[num+1]) {
        p.drawRect(i[1],i[2],i[3]-i[1],i[4]-i[2]);
        p.drawText(i[1]+3,i[4]+3,i[3]-i[1],20,Qt::AlignLeft,name[i[0]]);
    }
    pen.setBrush(Qt::yellow);
    p.setPen(pen);
    for (auto i : mp_miss[num+1]) {
        p.drawRect(i[1],i[2],i[3]-i[1],i[4]-i[2]);
        p.drawText(i[1]+3,i[4]+3,i[3]-i[1],20,Qt::AlignLeft,name[i[0]]);
    }
    lab->setPixmap(QPixmap::fromImage(*img));
    lab->adjustSize();
}

void MainWindow::on_clicked_next() {
    num = (num+1) % LEN;
    show_img();
}

void MainWindow::on_clicked_last() {
    num = (num+LEN-1) % LEN;
    show_img();
}

void MainWindow::on_clicked_go() {
    string tmp = cur->text().toStdString();
    if (tmp.size() > 6) {
        QMessageBox::warning(this,"input error","too long");
        return;
    }
    for (char c : tmp) {
        if (!isdigit(c)) {
            QMessageBox::warning(this,"input error","not integer");
            return;
        }
    }
    int t = stoi(tmp);
    if (t < 1 || t > LEN) {
        QMessageBox::warning(this,"input error","out of range");
        return;
    }
    num = t - 1;
    show_img();
}

MainWindow::~MainWindow()
{

}
