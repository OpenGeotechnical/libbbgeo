#include "soiltypetablemodel.h"
#include <QColor>
#include <QDebug>

SoilTypeTableModel::SoilTypeTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

SoilTypeTableModel::SoilTypeTableModel(QList<SoilType *> soilTypes, QObject *parent, bool maximized)
{
    Q_UNUSED(parent)
    m_soilTypes = soilTypes;
    m_maximized = maximized;
}

int SoilTypeTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_soilTypes.count();
}

int SoilTypeTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if(m_maximized)
        return 24;
    else
        return 1;
}

QVariant SoilTypeTableModel::data(const QModelIndex &index, int role) const
{
    if((!index.isValid())||(index.row()<0)||(index.row()>m_soilTypes.count()))
        return QVariant();
    else{
        SoilType *st = m_soilTypes[index.row()];
        if(role == Qt::DisplayRole){
            if(m_maximized){
                switch(index.column()){
                    case 0: return QVariant(QString("%1").arg(st->name()));
                    case 1: return QVariant(QString("%1").arg(st->description()));
                    case 2: return QVariant(QString("%1").arg(st->source()));
                    case 3: return QVariant(QString("%1").arg(st->yDry()));
                    case 4: return QVariant(QString("%1").arg(st->ySat()));
                    case 5: return QVariant(QString("%1").arg(st->c()));
                    case 6: return QVariant(QString("%1").arg(st->phi()));
                    case 7: return QVariant(QString("%1").arg(st->upsilon()));
                    case 8: return QVariant(QString("%1").arg(st->k()));
                    case 9: return QVariant(QString("%1").arg(st->mcUpsilon()));
                    case 10: return QVariant(QString("%1").arg(st->mcE50()));
                    case 11: return QVariant(QString("%1").arg(st->hsE50()));
                    case 12: return QVariant(QString("%1").arg(st->hsEoed()));
                    case 13: return QVariant(QString("%1").arg(st->hsEur()));
                    case 14: return QVariant(QString("%1").arg(st->hsM()));
                    case 15: return QVariant(QString("%1").arg(st->sscLambda()));
                    case 16: return QVariant(QString("%1").arg(st->sscKappa()));
                    case 17: return QVariant(QString("%1").arg(st->sscMu()));
                    case 18: return QVariant(QString("%1").arg(st->cp()));
                    case 19: return QVariant(QString("%1").arg(st->cs()));
                    case 20: return QVariant(QString("%1").arg(st->cap()));
                    case 21: return QVariant(QString("%1").arg(st->cas()));
                    case 22: return QVariant(QString("%1").arg(st->cv()));
                    case 23: return QVariant(QString("%1").arg(st->color()));
                    default: return QVariant();
                }
            }else{
                switch(index.column()){
                case 0: return QVariant(QString("(%1) %2").arg(st->id()).arg(st->name()));
                    default: return QVariant();
                }
            }
        }else if (role==Qt::BackgroundColorRole){
                return QVariant(QColor(st->color()));
            }
    }
    return QVariant();
}

QVariant SoilTypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if(m_maximized){
            switch (section) {
                case 0: return tr("name");
                case 1: return tr("description");
                case 2: return tr("source");
                case 3: return tr("y;dry");
                case 4: return tr("y;sat");
                case 5: return tr("c");
                case 6: return tr("phi");
                case 7: return tr("upsilon");
                case 8: return tr("k");
                case 9: return tr("MC;upsilon");
                case 10: return tr("MC;E50");
                case 11: return tr("HS;E50");
                case 12: return tr("HS;Eoed");
                case 13: return tr("HS;Eur");
                case 14: return tr("HS;m");
                case 15: return tr("SSC;lambda");
                case 16: return tr("SSC;kappa");
                case 17: return tr("SSC;mu");
                case 18: return tr("Cp");
                case 19: return tr("Cs");
                case 20: return tr("Cap");
                case 21: return tr("Cas");
                case 22: return tr("cv");
                case 23: return tr("color");
                default:  return QVariant();
            }
        }
        else{
            switch (section) {
                case 0: return tr("name");
                default: return QVariant();
            }
        }
    }
    return QVariant();
}

bool SoilTypeTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    if(index.isValid() && index.row()>0 && index.row() < m_soilTypes.count()){
        SoilType *st = m_soilTypes.at(index.row());
        if(st==NULL){
            qDebug() << "Error in SoilTypeTableModel::setData, Soiltypes = NULL.";
            return false;
        }
        switch(index.column()){
            case 0: st->setName(value.toString()); break;
            case 1: st->setDescription(value.toString()); break;
            case 2: st->setSource(value.toString()); break;
            case 3: st->setYdry(value.toDouble()); break;
            case 4: st->setYsat(value.toDouble()); break;
            case 5: st->setC(value.toDouble()); break;
            case 6: st->setPhi(value.toDouble()); break;
            case 7: st->setUpsilon(value.toDouble()); break;
            case 8: st->setK(value.toDouble()); break;
            case 9: st->setMCUpsilon(value.toDouble()); break;
            case 10: st->setMCE50(value.toDouble()); break;
            case 11: st->setHSE50(value.toDouble()); break;
            case 12: st->setHSEoed(value.toDouble()); break;
            case 13: st->setHSEur(value.toDouble()); break;
            case 14: st->setHSm(value.toDouble()); break;
            case 15: st->setSSClambda(value.toDouble()); break;
            case 16: st->setSSCkappa(value.toDouble()); break;
            case 17: st->setSSCmu(value.toDouble()); break;
            case 18: st->setCp(value.toDouble()); break;
            case 19: st->setCs(value.toDouble()); break;
            case 20: st->setCap(value.toDouble()); break;
            case 21: st->setCas(value.toDouble()); break;
            case 22: st->setCv(value.toDouble()); break;
            case 23: st->setColor(value.toString()); break;
            default: break;
        }
        st->setDataChanged(true);
        emit dataChanged(index, index);
    }
    return false;
}

Qt::ItemFlags SoilTypeTableModel::flags(const QModelIndex &index) const
{
    if(index.row()==0 || !index.isValid()){
        return Qt::ItemIsEnabled;
    }
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
