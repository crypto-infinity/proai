r"""
Deep Neural Networks (DNN) helper module.
This module provides a simple interface for creating and training deep neural networks with PyTorch without reimplementing common functions.

Author: Gabriele Scorpaniti, 2025
"""

# Standard Libraries
import os
import random

# Data Science Libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#PyTorch Libraries
import torch
import torch.utils.data as data_utils

#Scikit-learn Library
from sklearn.model_selection import KFold

#Dataclass Library
from dataclasses import dataclass, field

class Helper:
    """
    Helper functions for CNN training and evaluation.
    """

    @staticmethod
    def plot_images(dataset, classes, iteration=0, num_row=3, num_col=5):
       """
       Visualizes a batch of images from the dataset.
       Args:
            dataset: PyTorch dataset.
            classes: List of class names.
            iteration: Iteration number for batch visualization.
       """

       fig, axes = plt.subplots(num_row, num_col, figsize=(10*num_row,2*num_col))

       for i in range(num_row*num_col):
           ax = axes[i//num_col, i%num_col]
           ax.imshow(Helper.back_to_image(dataset[iteration * num_row * num_col + i][0]))
           ax.set_title('{}'.format(classes[int(dataset[iteration * num_row * num_col + i][1])]))

       plt.tight_layout()
       plt.show()
       iteration += 1

    @staticmethod
    def plot_class_distribution(dataset, type="training"):
        """
        Pltots the class distribution of a dataset.
        Args:
            dataset: PyTorch dataset.
            type: Type of dataset (training, validation or test).
        """

        #Check if the dataset is a valid PyTorch dataset
        if not hasattr(dataset, 'targets'):
            raise ValueError("Il dataset non è un dataset PyTorch valido.")

        #Dataset classes count
        df = pd.DataFrame(dataset.targets, columns=['label'])
        df['label'] = df['label'].map(lambda x: dataset.classes[x])
        
        #Plotting
        df['label'].value_counts().plot(kind='bar', figsize=(12, 6))
        plt.title(f'Distribuzione delle classi nel {type} set')
        plt.xlabel('Classi')
        plt.ylabel('Numero di samples')
        plt.xticks(rotation=45)
        plt.show()

    @staticmethod
    def back_to_image(img):
        """
        Convert a tensor to an image.
        
        Args:
        tensor : torch.Tensor
            The input tensor to be converted to an image.
        
        Returns:
        numpy.ndarray
            The converted image as a NumPy array.
        """

        img = img / 2 + 0.5
        npimg = img.numpy()
        return np.transpose(npimg, (1, 2, 0))

    @staticmethod
    def set_seed(seed):
        """
        Set the random seed for reproducibility.
        
        Args:
        seed : int
            The random seed to be set.
        """
        
        random.seed(seed)
        os.environ['PYTHONHASHSEED'] = str(seed)
        np.random.seed(seed)
        torch.manual_seed(seed)
        if torch.cuda.is_available():
            torch.cuda.manual_seed_all(seed)

    @staticmethod
    def set_device():
        """
        Set the device to GPU if available, otherwise CPU.
        
        Returns:
        torch.device
            The device to be used for computations.
        """
        
        return torch.device("cuda" if torch.cuda.is_available() else "cpu")

class EarlyStopping:
    """
    Implements early stopping to terminate training when the validation loss does not improve for a specified number of epochs.
    
    Args:
    save_path : str
        Path to save the model checkpoint.
    patience : int
        Number of epochs with no improvement after which training will be stopped.
    min_delta : float
        Minimum change in the monitored quantity to qualify as an improvement.
    """
    
    
    def __init__(self, save_path, patience=5, min_delta=0):
        
        # Initialize the early stopping parameters

        self.save_path = save_path
        self.patience = patience
        self.min_delta = min_delta
        self.min_val_loss = None
        self.counter = 0
        self.early_stop = False

    def __call__(self, validation_loss, model):

        # First Epoch
        if self.min_val_loss is None:     
          self.min_val_loss = validation_loss
          self.save_checkpoint(model)

        # Epoch with improvement
        elif (self.min_val_loss - validation_loss) > self.min_delta:
          self.min_val_loss = validation_loss
          self.save_checkpoint(model)
          self.counter = 0

        # No improvement, stop training if patience is reached
        else:
          self.counter +=1
          if self.counter >= self.patience:
            self.early_stop = True

    def save_checkpoint(self, model):
      torch.save(model.state_dict(), self.save_path)

@dataclass
class Experiment:
    """
    Class to manage the training of a deep neural network.
    This class handles the initialization of the model, loss function, optimizer, and early stopping mechanism.
    It also provides methods for training and validating the model, as well as saving checkpoints.
    
    Args:
    name : str
        Name of the experiment.
    checkpoints_folder : str
        Path to the folder where checkpoints will be saved.
    checkpoint_name : str
        Name of the checkpoint file.
    model : object
        The model class to be trained.
    loss_fn : object
        The loss function class to be used for training.
    optimizer : object
        The optimizer class to be used for training.
    val_mse : float, optional
        Initial validation mean squared error (MSE) value. Default is None.
    lr : float, optional
        Learning rate for the optimizer. Default is 1e-5.
    epochs : int, optional
        Number of epochs for training. Default is 600.
    metrics : list, optional
        List of metrics to be used for evaluation. Default is an empty list.
    use_early_stopping : bool
        Whether to use early stopping. Default is False.
    patience : int, optional
        Number of epochs with no improvement after which training will be stopped. Default is 10.
    min_delta : float, optional
        Minimum change in the monitored quantity to qualify as an improvement. Default is 0.
    early_stopping : object, optional
        Early stopping object. Default is None.
    epoch_count : list, optional
        List to store the epoch count. Default is an empty list.
    train_loss_values : list, optional
        List to store the training loss values. Default is an empty list.
    val_loss_values : list, optional
        List to store the validation loss values. Default is an empty list.
    color : str
        Color for plotting. Default is 'blue'.
    alpha : float
        Alpha value for plotting. Default is 0.5.
    plt_args_training : dict, optional
        Additional arguments for training plot. Default is an empty dictionary.
    plt_args_validation : dict, optional
        Additional arguments for validation plot. Default is an empty dictionary.
    """
  
    #General parameters
    name: str
    checkpoints_folder: str
    checkpoint_name:str
    model: object

    #Model hyperparameters
    loss_fn : object
    optimizer: object
    val_mse: float = None
    lr: float = 1e-5
    
    # Early stopping
    use_early_stopping: bool = False
    patience: int = 10
    min_delta: float = 0
    early_stopping: object = None
    
    #Epochs
    epochs: int = 600
    epoch_count: list = field(default_factory=list)
    
    #Training and validation loss
    val_loss_values: list = field(default_factory=list)
    train_loss_values: list = field(default_factory=list)
    
    #Plotting arguments
    color: str = "blue"
    alpha: float = 0.5
    plt_args_training: dict = field(default_factory=dict)
    plt_args_validation: dict = field(default_factory=dict)


    def __post_init__(self):
        
        # Set the device to GPU if available, otherwise CPU
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        
        # Initialize the model, loss function, and optimizer
        self.model = self.model()
        self.model = self.model.to(self.device)
        
        self.loss_fn = self.loss_fn()
        self.loss_fn = self.loss_fn.to(self.device)
        
        self.optimizer = self.optimizer(params=self.model.parameters(),
                                lr=self.lr)
        
        # Initialize the early stopping object if required
        if self.use_early_stopping:
        
            early_stopping_folder = os.path.join(self.checkpoints_folder, "early_stopping", self.name)
            os.makedirs(early_stopping_folder, exist_ok = True)
            
            self.early_stopping = EarlyStopping(save_path=early_stopping_folder+self.name,
                                                patience=self.patience,
                                                min_delta=self.min_delta)
        
        # Checkpointing
        self.checkpoints_folder = os.path.join(self.checkpoints_folder, "checkpoints", self.name)
        os.makedirs(self.checkpoints_folder, exist_ok = True)
        self.checkpoint_save_path = os.path.join(self.checkpoints_folder, self.checkpoint_name)

class Trainer:
    """
    Class to manage the training of a deep neural network.
    This class handles the initialization of the model, loss function, optimizer, and early stopping mechanism.
    It also provides methods for training and validating the model, as well as saving checkpoints.
    """

    @staticmethod
    def fit(exp:Experiment, trainloader, valloader):

        exp.train_loss_values = []
        exp.val_loss_values = []

        for epoch in range(exp.epochs):

            exp.model.train()
            loss_epoch = 0

            for i, data in enumerate(trainloader, 0):

                X = data[0]
                y = data[1]

                y_pred = exp.model(X)
                loss = exp.loss_fn(y_pred, y)

                loss_epoch += loss

                exp.optimizer.zero_grad()

                loss.backward()

                exp.optimizer.step()

            loss_val = 0
            exp.model.eval()

            for j, data in enumerate(valloader, 0):

                X = data[0]
                y = data[1]

                with torch.no_grad():

                    y_pred = exp.model(X)
                    loss = exp.loss_fn(y_pred.squeeze(-1), y)

                    loss_val += loss

            exp.epoch_count.append(epoch)
            exp.train_loss_values.append(loss_epoch.detach().numpy()/len(trainloader))
            exp.val_loss_values.append(loss_val.detach().numpy()/len(valloader))

            print(f"Epoca: {epoch} |  Train Loss: {loss_epoch/len(trainloader)} | Val Loss: {loss_val/len(valloader)} ")

            if exp.use_early_stopping:
                exp.early_stopping(loss_val/len(valloader), exp.model)
                if exp.early_stopping.early_stop:
                    print("Early stopping all'epoca:", epoch)
                    exp.model.load_state_dict(torch.load(exp.checkpoint_save_path))
                    break

    @staticmethod
    def evaluate(exp:Experiment, testloader):
        """
        Evaluate the model on the test set.
        
        Args:
            exp: Experiment object containing the model and evaluation parameters.
            testloader: DataLoader for the test set.
        """
        
        exp.model.eval()
        loss_test = 0

        for i, data in enumerate(testloader, 0):

            X = data[0]
            y = data[1]

            with torch.no_grad():

                y_pred = exp.model(X)
                loss = exp.loss_fn(y_pred.squeeze(-1), y)

                loss_test += loss

        return loss_test.item()/len(testloader)


## Modify this with subsetsampler
@dataclass    
class CrossValidation():
    """
    Manages cross-validation for training and evaluating a model.
    """
    
    def __init__(self, experiments: list[Experiment], X: torch.tensor, y: torch.tensor, test_dl: data_utils.DataLoader, n_splits, shuffle=True, seed=None):
        """
        Initialize the cross-validation object.
        
        Args:
            n_splits: Number of splits for cross-validation.
            shuffle: Whether to shuffle the data before splitting.
            random_state: Random seed for reproducibility.
        """
        
        self.dataset = data_utils.TensorDataset(X, y)
        self.test_dl = test_dl

        self.experiments = experiments

        self.n_splits = n_splits
        self.shuffle = shuffle
        self.seed = seed

    def split_and_train(self):
        """
        Splits the dataset into training and validation sets and trains the model.
        """

        # Kfold cross-validation
        
        kf = KFold(n_splits=self.n_splits, shuffle=self.shuffle, random_state=self.seed)

        for fold, (train_idx, val_idx) in enumerate(kf.split(self.X)):

            train_sampler = data_utils.SubsetRandomSampler(train_idx)
            val_sampler = data_utils.SubsetRandomSampler(val_idx)

            # Creating DataLoaders for this fold
            train_dl_split = data_utils.DataLoader(self.dataset, batch_size=64, shuffle=True, sampler=train_sampler)
            val_dl_split = data_utils.DataLoader(self.dataset, batch_size=64, shuffle=False, sampler=val_sampler)
            
            for exp in self.experiments:
                # Training models for this fold
                Trainer.fit(exp, train_dl_split, val_dl_split)

                # Evaluate the fold on the test set
                test_loss = Trainer.evaluate(exp, self.test_dl)
                print(f"Test Loss for {exp.name} on fold {fold}: {test_loss}")
