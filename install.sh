#---------------------------------------------------------------
SOFTWARE_CONFIG="assets/private/.config"
QTIL_CONFIG="assets/engines/QTIL/.config"
QTIL_BACKUP="assets/engines/QTIL/.backup"
DESCRIPTOR_PATH="assets/engines/QTIL/descriptors"
HISTORY="assets/private/.history"
ROOT=$(pwd)
#---------------------------------------------------------------
PATH="path $ROOT/DATA_BASE/"
MODE="mode open"
DESCRIPTORS="descriptors $ROOT/$DESCRIPTOR_PATH/"
WINDOW_SIZE="taille_des_fenetres 500"
WINDOW_COUNT="nombre_de_barre 250"
QUANTIFICATION="quantification 4"
PIXEL_MARGIN="pixel_margin 50"
#---------------------------------------------------------------
echo "Installation..."

#---------------------------------------------------------------
# Software config
echo "Create settings for QTIL software..." 
echo $PATH > $SOFTWARE_CONFIG
echo $MODE >> $SOFTWARE_CONFIG

#---------------------------------------------------------------
# QTIL settings
echo "Create settings for QTIL search engine..." 
echo $PATH > $QTIL_CONFIG
echo $DESCRIPTORS >> $QTIL_CONFIG
echo $WINDOW_SIZE >> $QTIL_CONFIG
echo $WINDOW_COUNT >> $QTIL_CONFIG
echo $QUANTIFICATION >> $QTIL_CONFIG
echo $PIXEL_MARGIN >> $QTIL_CONFIG

#---------------------------------------------------------------
# QTIL backup
echo "Create settings backup for QTIL search engine..." 
echo $PATH > $QTIL_BACKUP
echo $DESCRIPTORS >> $QTIL_BACKUP
echo $WINDOW_SIZE >> $QTIL_BACKUP
echo $WINDOW_COUNT >> $QTIL_BACKUP
echo $QUANTIFICATION >> $QTIL_BACKUP
echo $PIXEL_MARGIN >> $QTIL_BACKUP

#---------------------------------------------------------------
echo "Create descriptors directory..."
/bin/mkdir -p $DESCRIPTOR_PATH

#---------------------------------------------------------------
echo "Create empty history..."
> $HISTORY

#---------------------------------------------------------------
echo "Installation done successfully !!"
